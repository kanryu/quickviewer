#include <QGraphicsPixmapItem>
#include "shadermanager.h"
#include "qvapplication.h"

#ifndef QV_WITHOUT_OPENGL
#include <QtOpenGL>
#include <QtOpenGL/private/qgraphicsshadereffect_p.h>

class LanczosShaderEffect : public QGraphicsShaderEffect
{
public:
    LanczosShaderEffect(QObject *parent = 0) : QGraphicsShaderEffect(parent) { }
    void createKernel(float delta, int *size);
    void createOffsets(int count, float width, Qt::Orientation direction);
    void setViewWidth(int viewWidth) { m_viewWidth = viewWidth; }
    int viewWidth() { return m_viewWidth; }

protected:
    void setUniforms(QGLShaderProgram *program)
    {
        program->setUniformValueArray((const char*)("offsets"), (const QVector2D *)&m_offsets, BLOCK);
        program->setUniformValueArray((const char*)("kernel"), (const QVector4D *)&m_kernel, BLOCK);
    }
private:
    enum {BLOCK = 16} e;
    QVector2D m_offsets[16];
    QVector4D m_kernel[16];
    int m_viewWidth;
};

inline static float sinc(float x)
{
    return std::sin(x * M_PI) / (x * M_PI);
}

inline static float lanczos(float x, float a)
{
    if (qFuzzyCompare(x + 1.0, 1.0))
        return 1.0;

    if (qAbs(x) >= a)
        return 0.0;

    return sinc(x) * sinc(x / a);
}


void LanczosShaderEffect::createKernel(float delta, int *size)
{
    const float a = 2.0;

    // The two outermost samples always fall at points where the lanczos
    // function returns 0, so we'll skip them.
    const int sampleCount = qBound(3, qCeil(delta * a) * 2 + 1 - 2, 29);
    const int center = sampleCount / 2;
    const int kernelSize = center + 1;
    const float factor = 1.0 / delta;

    QVector<float> values(kernelSize);
    float sum = 0;

    for (int i = 0; i < kernelSize; i++) {
        const float val = lanczos(i * factor, a);
        sum += i > 0 ? val * 2 : val;
        values[i] = val;
    }

    memset(m_kernel, 0, BLOCK * sizeof(QVector4D));

    // Normalize the kernel
    for (int i = 0; i < kernelSize; i++) {
        const float val = values[i] / sum;
        m_kernel[i] = QVector4D(val, val, val, val);
    }

    *size = kernelSize;
}

void LanczosShaderEffect::createOffsets(int count, float width, Qt::Orientation direction)
{
    memset(m_offsets, 0, BLOCK * sizeof(QVector2D));
    for (int i = 0; i < count; i++) {
        m_offsets[i] = (direction == Qt::Horizontal) ?
                       QVector2D(i / width, 0) : QVector2D(0, i / width);
    }
}
#endif


//////////////////////////////////////////////////////
/// \brief ImageEffectManager::ImageEffectManager
/// \param parent
ShaderManager::ShaderManager(QObject *parent)
    : QObject(parent)
    , m_oldEffect(qvEnums::Bilinear)
    , pageCnt(0)
{
#ifndef QV_WITHOUT_OPENGL
    loadShader(m_bicubic, qApp->BicubicShaderPath());
    loadShader(m_lanczos, qApp->LanczosShaderPath());
#endif
}

void ShaderManager::loadShader(QByteArray& target, QString path)
{
    if(!QDir::isAbsolutePath(path)) {
        path = QString("%1/%2").arg(qApp->applicationDirPath()).arg(path);
    }
    QFile file(path);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
       target = file.readAll();
    }
}

#ifndef QV_WITHOUT_OPENGL
void ShaderManager::prepare(QGraphicsPixmapItem *item, const ImageContent &ic, QSize size)
#else
void ShaderManager::prepare(QGraphicsPixmapItem *item, const ImageContent &, QSize)
#endif
{
    if(!item)
        return;
    qvEnums::ShaderEffect effect = qApp->Effect();
    switch(effect) {
    default: break;
    case qvEnums::CpuBicubic:
    case qvEnums::CpuSpline16:
    case qvEnums::CpuSpline36:
    case qvEnums::CpuLanczos3:
    case qvEnums::Bilinear:
    case qvEnums::BilinearAndCpuBicubic:
    case qvEnums::BilinearAndCpuSpline16:
    case qvEnums::BilinearAndCpuSpline36:
    case qvEnums::BilinearAndCpuLanczos:
        if(m_oldEffect != qvEnums::Bilinear)
            item->setTransformationMode(Qt::SmoothTransformation);
        if(m_oldEffect > qvEnums::UsingSomeShader)
            item->setGraphicsEffect(nullptr);
        break;
    case qvEnums::NearestNeighbor:
        if(m_oldEffect != qvEnums::NearestNeighbor)
            item->setTransformationMode(Qt::FastTransformation);
        if(m_oldEffect > qvEnums::UsingSomeShader)
            item->setGraphicsEffect(nullptr);
        break;
#ifndef QV_WITHOUT_OPENGL
    case qvEnums::Bicubic:
        if(m_oldEffect == qvEnums::NearestNeighbor)
            item->setTransformationMode(Qt::SmoothTransformation);
        if(m_oldEffect != qvEnums::Bicubic) {
            QGraphicsShaderEffect * shader = nullptr;
            if(m_bicubic.length() > 0) {
                shader = new QGraphicsShaderEffect(this);
                shader->setPixelShaderFragment(m_bicubic);
            }
            item->setGraphicsEffect(shader);
        }
        break;
    case qvEnums::Lanczos:
        if(m_oldEffect == qvEnums::NearestNeighbor)
            item->setTransformationMode(Qt::SmoothTransformation);
        if(m_oldEffect != qvEnums::Lanczos) {
            QGraphicsShaderEffect * shader = nullptr;
            if(m_lanczos.length() > 0) {
                auto lanczos = new LanczosShaderEffect(this);
                lanczos->setPixelShaderFragment(m_lanczos);

                int sw = ic.ImportSize.width();
                //int sh = ic.ImportSize.height();
                qreal pow = 1.0*size.width()/sw;
//                if(pow*8 < 1) {
//                    pow *= 2;
//                } else if(pow*4 < 1){
//                    pow *= 1;
//                } else if(pow*2 < 1){
//                    pow *= 1;
//                }
                int kernelSize;
                lanczos->createKernel(1.0/pow, &kernelSize);
//                qDebug() << 1.0/pow << kernelSize;
                lanczos->createOffsets(kernelSize, sw, Qt::Horizontal);

//                int sw2 = qMax(sw, sh);
//                int swb = 1;
//                while(sw2 > swb)
//                  swb <<= 1;
//                lanczos->createOffsets(kernelSize, swb, Qt::Horizontal);

                shader = lanczos;
            }
            item->setGraphicsEffect(shader);
        } else {
            auto lanczos = dynamic_cast<LanczosShaderEffect*>(item->graphicsEffect());
            if(!lanczos)
                break;
            if(lanczos->viewWidth() == size.width())
                break;
            int sw = ic.ImportSize.width();
            //int sh = ic.ImportSize.height();
            qreal pow = 1.0*size.width()/sw;
            int kernelSize;
            lanczos->createKernel(1.0/pow, &kernelSize);
            lanczos->createOffsets(kernelSize, sw, Qt::Horizontal);

//            int sw2 = qMax(sw, sh);
//            int swb = 1;
//            while(sw2 > swb)
//              swb <<= 1;
//            lanczos->createOffsets(kernelSize, swb, Qt::Horizontal);
        }
        break;
#endif
    }
    pageCnt++;
}

void ShaderManager::prepareFinished()
{
    pageCnt=0;
    m_oldEffect = qApp->Effect();
}

