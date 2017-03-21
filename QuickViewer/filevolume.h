#ifndef FILELIST_H
#define FILELIST_H

#include <QList>
#include <QObject>
#include <QDir>
#include <QPixmap>

class IFileVolume : public QObject
{
    Q_OBJECT
//    Q_DISABLE_COPY(IFileVolume)
public:
    explicit IFileVolume(QObject *parent=0);
    virtual ~IFileVolume() {}
    /**
     * @brief 指定されたファイルまたはディレクトリのpathからIFileVolumeのインスタンスを返すファクトリ関数
     * @return IFileVolumeインターフェイスを継承したオブジェクト。生成に失敗した場合はnull
     */
    static IFileVolume* CreateVolume(QObject* parent, QString path);
    /**
     * @brief 現在のファイルパスを返す
     * @return
     */
    virtual QString currentPath()=0;
    /**
     * @brief currentImage 現在の画像(ページ)を返す。１度呼び出すとキャッシュされ、ページまたはボリュームが変更されるまで同じインスタンスを返す
     * @return
     */
    virtual QPixmap currentImage()=0;

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
    virtual bool setIndexedFile(int idx)=0;
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

//signals:
//    /**
//     * @brief changing 次に表示すべき画像が通知される。View側はその画像を画面に表示すべきである
//     */
//    void changing(QImage image) const;
//    /**
//     * @brief changed 次に表示される画像のファイルパスが通知される。アプリ本体が情報を得るのはこのタイミング
//     * @param path
//     */
//    void changed(QString path) const;

protected:
    /**
     * @brief 6ページ分の画像をキャッシュする。
     * 単ページの場合m_cachedImages[2]、見開きの場合m_cachedImages[2],m_cachedImages[3]が使われる。
     * ページ変更が行われた場合、前進するならば[0][1]を破棄し[3][4]を先読み、後退するならば[3][4]を破棄し[0][1]を先読みする。
     * 無効なページの場合QImage()で置き換える。
     */
    QList<QPixmap> m_cachedImages;
    int m_cnt;
};



#endif // FILELIST_H
