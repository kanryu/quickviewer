#ifndef FILELIST_H
#define FILELIST_H

#include <QPixmap>
#include <QImage>
#include <QtConcurrent>
#include <QMutex>
#include "exif.h"

struct ImageContent
{
public:
    QPixmap Image;
    QSize BaseSize;
    QString Path;
    easyexif::EXIFInfo Info;

    ImageContent(){}
    ImageContent(QPixmap image, QString path, QSize size, easyexif::EXIFInfo info)
        : Image(image), Path(path), BaseSize(size), Info(info) {
    }

    ImageContent(const ImageContent& rhs)
        : Image(rhs.Image), Path(rhs.Path), BaseSize(rhs.BaseSize), Info(rhs.Info) {
    }
    inline ImageContent& ImageContent::operator=(const ImageContent &rhs)
    {
        Image = rhs.Image;
        Path = rhs.Path;
        BaseSize = rhs.BaseSize;
        Info = rhs.Info;
        return *this;
    }
    bool wideImage() const {return BaseSize.width() > BaseSize.height(); }
};



class IFileVolume : public QObject
{
    Q_OBJECT
//    Q_DISABLE_COPY(IFileVolume)
public:
    typedef QFuture<ImageContent> future_image;

    explicit IFileVolume(QObject *parent=0);
    virtual ~IFileVolume() {}
    /**
     * @brief 指定されたファイルまたはディレクトリのpathからIFileVolumeのインスタンスを返すファクトリ関数
     * @return IFileVolumeインターフェイスを継承したオブジェクト。生成に失敗した場合はnull
     */
    static IFileVolume* CreateVolume(QObject* parent, QString path, QString subfilename=nullptr);
    /**
     * @brief isImageFile そのファイルが画像ファイルかを拡張子から調べる
     * @param path
     * @return 画像と思われる場合true
     */
    static bool isImageFile(QString path);

    static ImageContent futureLoadImageFromFileVolume(IFileVolume* volume, QString path);
    virtual bool isArchive() const { return true; }
    /**
     * @brief 現在のファイルパスを返す
     * @return
     */
    virtual QString currentPath()=0;
    /**
     * @brief currentImage 現在の画像(ページ)を返す。１度呼び出すとキャッシュされ、ページまたはボリュームが変更されるまで同じインスタンスを返す
     * @return
     */
    virtual const ImageContent currentImage()=0;
    /**
     * @brief volumePath ボリュームのpathを返す。通常コンストラクタのpathがそのまま返ってくる
     */
    virtual QString volumePath()=0;
    /**
     * @brief 一つ次のページに移動する（一度に複数の画像を表示する場合、その最初の画像に制御が移る）
     * @return 成功/失敗(ファイルリスト終端等)
     */
    bool nextPage();
    /**
     * @brief 一つ前のページに移動する（一度に複数の画像を表示する場合、前ページの最後の画像に制御が移ることに注意）
     * @return 成功/失敗(ファイルリスト終端等)
     */
    bool prevPage();
    bool findPageByIndex(int idx);
    /**
     * @brief 現在のファイルリストの中で次のファイルに移動する
     * @return 成功/失敗(ファイルリスト終端等)
     */
    virtual bool nextFile()=0;
    /**
     * @brief 現在のファイルリストの中で前のファイルに移動する
     * @return 成功/失敗(ファイルリスト終端等)
     */
    virtual bool prevFile()=0;
    /**
     * @brief 現在のファイルリストの中で指定されたidx値に対応するファイルに移動する(最大値はディレクトリまたはアーカイブの画像数-1)
     * @return 成功/失敗(ファイルリスト終端等)
     */
    virtual bool findImageByIndex(int idx)=0;
    /**
     * @brief 現在のファイルリストの中で指定されたファイル名に対応するファイルに移動する
     * @return 成功/失敗(ファイルが見つからない等)
     */
    virtual bool findImageByName(QString name)=0;
    /**
     * @brief loadImageByName 内部カウンタを進めずにファイルリストの中で指定されたファイル名に対応する画像を読み込んで返す
     * @return ロードに失敗すれば空インスタンス
     */
    virtual QByteArray loadByteArrayByName(const QString& name)=0;
    /**
     * @brief ボリュームが持つページ数を返す
     * @return ボリュームが持つページ数
     */
    virtual int size()=0;
    /**
     * @brief on_ready アプリの準備が終わった段階で呼び出される。最初に、あるいは次に表示すべき画像およびそのファイルパスがemitされる
     */
    void on_ready();
    /**
     * @brief pageCount 現在のページを返す
     */
    int pageCount() { return m_cnt; }

//    QPixmap getIndexedImage(int idx);
//    QString getIndexedImageName(int idx) { return m_filelist[idx]; }
//    QString currentImageName() const { return m_filelist[m_cnt]; }
    const ImageContent getIndexedImageContent(int idx);


protected:
    /**
     * @brief m_cnt ボリューム内のファイルカウンタ
     */
    int m_cnt;
    QList<QString> m_filelist;
    future_image m_currentCache;

    QMap<int, future_image> m_imageCache;
    QList<int> m_pageCache;

    QMutex m_mutex;
};



#endif // FILELIST_H
