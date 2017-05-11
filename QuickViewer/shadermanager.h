#ifndef IMAGESHADEREFFECT_H
#define IMAGESHADEREFFECT_H

#include <QtGui>
#include <QGLShaderProgram>
#include <QGraphicsScene>
#include <QMetaEnum>
#include "filevolume.h"
#include "qv_init.h"

/**
 * @brief The ShaderManager class
 * customizing the shader effec oft QGraphicsPixmapItem,
 * which can use a fragment shader
 */
class ShaderManager : public QObject
{
    Q_OBJECT
public:
    ShaderManager(QObject *parent = 0);
    /**
     * @brief prepare shader for each page
     * @param ic
     */
    void prepare(QGraphicsPixmapItem* item, const ImageContent& ic, QSize size);
    /**
     * @brief prepareFinished must be called once after all prepare()
     */
    void prepareFinished();
    void prepareInitialize() { m_oldEffect = qvEnums::UnPrepared; pageCnt=0;}

    static QString shaderEffectToString(qvEnums::ShaderEffect effect)
    {
        QMetaEnum metaEnum = QMetaEnum::fromType<qvEnums::ShaderEffect>();
        return metaEnum.valueToKey(effect);
    }
    static qvEnums::ShaderEffect stringToShaderEffect(QString effect)
    {
        QMetaEnum metaEnum = QMetaEnum::fromType<qvEnums::ShaderEffect>();
        return (qvEnums::ShaderEffect)metaEnum.keysToValue(effect.toLatin1());
    }

private:
    void loadShader(QByteArray& target, QString path);

//    ShaderEffect m_effect;
    qvEnums::ShaderEffect m_oldEffect;
    int pageCnt;
    QByteArray m_bicubic;
    QByteArray m_lanczos;
};

#endif // IMAGESHADEREFFECT_H
