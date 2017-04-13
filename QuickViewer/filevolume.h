#ifndef FILELIST_H
#define FILELIST_H

#include <QPixmap>
#include <QImage>
#include <QtConcurrent>
#include <QMutex>
#include "exif.h"
#include "fileloader.h"
#include "timeorderdcache.h"

struct ImageContent
{
public:
    QPixmap Image;
    QSize BaseSize;
    QSize ImportSize;
    QString Path;
    easyexif::EXIFInfo Info;

    ImageContent(){}
    ImageContent(QPixmap image, QString path, QSize size, easyexif::EXIFInfo info)
        : Image(image), Path(path), BaseSize(size), ImportSize(image.size()), Info(info) {}
    ImageContent(const ImageContent& rhs)
        : Image(rhs.Image), Path(rhs.Path), BaseSize(rhs.BaseSize), ImportSize(rhs.ImportSize), Info(rhs.Info) {}
    inline ImageContent& operator=(const ImageContent &rhs)
    {
        Image = rhs.Image;
        Path = rhs.Path;
        BaseSize = rhs.BaseSize;
        ImportSize = rhs.ImportSize;
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
    enum CacheMode
    {
        Normal,
        FastFowrard,
        CoverOnly
    };

    typedef QFuture<ImageContent> future_image;

    explicit IFileVolume(QObject *parent, IFileLoader* loader);
    ~IFileVolume() {
        if(m_loader) {
            delete m_loader;
            m_loader = nullptr;
        }
    }
    /**
     * @brief 指定されたファイルまたはディレクトリのpathからIFileVolumeのインスタンスを返すファクトリ関数
     * @return IFileVolumeインターフェイスを継承したオブジェクト。生成に失敗した場合はnull
     */
    static IFileVolume* CreateVolume(QObject* parent, QString path, QString subfilename=nullptr);
    static IFileVolume* CreateVolumeWithOnlyCover(QObject* parent, QString path);

    static ImageContent futureLoadImageFromFileVolume(IFileVolume* volume, QString path);
    bool isArchive() const { return m_loader->isArchive(); }
    /**
     * @brief 現在のファイルパスを返す
     * @return
     */
    QString currentPath() {
        if(m_loader->isArchive())
            return m_filelist[m_cnt];
        else
            return QDir(m_loader->volumePath()).absoluteFilePath(m_filelist[m_cnt]);
    }
    QString getPathByFileName(QString name) {
        if(m_loader->isArchive())
            return "";
        else
            return QDir(m_loader->volumePath()).absoluteFilePath(name);
    }
    QString getIndexedFileName(int idx) {
        if(idx < 0 || idx >= m_filelist.size())
            return "";
        return m_filelist[idx];
    }
    QString getPathByIndex(int idx) {
        if(idx < 0 || idx >= m_filelist.size())
            return "";
        return QDir(m_loader->volumePath()).absoluteFilePath(m_filelist[idx]);
    }
    void setCacheMode(CacheMode cachemode) { m_cacheMode = cachemode; }
    CacheMode cacheMode() const { return m_cacheMode; }

    /**
     * @brief currentImage 現在の画像(ページ)を返す。１度呼び出すとキャッシュされ、ページまたはボリュームが変更されるまで同じインスタンスを返す
     * @return
     */
    const ImageContent currentImage() { return m_currentCache.result(); }
    /**
     * @brief volumePath ボリュームのpathを返す。通常コンストラクタのpathがそのまま返ってくる
     */
    QString volumePath() { return m_loader->volumePath(); }
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
//    /**
//     * @brief 現在のファイルリストの中で次のファイルに移動する
//     * @return 成功/失敗(ファイルリスト終端等)
//     */
//    virtual bool nextFile()=0;
//    /**
//     * @brief 現在のファイルリストの中で前のファイルに移動する
//     * @return 成功/失敗(ファイルリスト終端等)
//     */
//    virtual bool prevFile()=0;
    /**
     * @brief 現在のファイルリストの中で指定されたidx値に対応するファイルに移動する(最大値はディレクトリまたはアーカイブの画像数-1)
     * @return 成功/失敗(ファイルリスト終端等)
     */
    bool findImageByIndex(int idx) {
        if(idx < 0 || idx >= m_filelist.size())
            return false;
        m_cnt = idx;
        return true;
    }

    /**
     * @brief 現在のファイルリストの中で指定されたファイル名に対応するファイルに移動する
     * @return 成功/失敗(ファイルが見つからない等)
     */
    bool findImageByName(QString name) {
        int idx = m_filelist.indexOf(name);
        if(idx < 0)
            return false;
        m_cnt = idx;
        return true;
    }

    /**
     * @brief loadImageByName 内部カウンタを進めずにファイルリストの中で指定されたファイル名に対応する画像を読み込んで返す
     * @return ロードに失敗すれば空インスタンス
     */
    QByteArray loadByteArrayByName(const QString& name) { return m_loader->getFile(name, m_mutex); }
    /**
     * @brief ボリュームが持つページ数を返す
     * @return ボリュームが持つページ数
     */
    int size() { return m_filelist.size(); }
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

    TimeOrderdCache<int, future_image> m_imageCache;
//    QMap<int, future_image> m_imageCache;
//    QList<int> m_pageCache;

    QMutex m_mutex;

    IFileLoader* m_loader;
    CacheMode m_cacheMode;
};



#endif // FILELIST_H
