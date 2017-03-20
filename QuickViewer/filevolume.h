#ifndef FILELIST_H
#define FILELIST_H

#include <QList>
#include <QObject>
#include <QDir>
#include <QImage>

class IFileVolume : public QObject
{
    Q_OBJECT
//    Q_DISABLE_COPY(IFileVolume)
public:
    explicit IFileVolume(QObject *parent=0) : QObject(parent) {}
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
    virtual QImage currentImage()=0;

public:
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
     * @brief 次のディレクトリまたはアーカイブに移動する
     * @return 成功/失敗(正常にファイルリストを取得できなかった場合)
     */
    virtual bool nextVolume()=0;
    /**
     * @brief 前のディレクトリまたはアーカイブに移動する
     * @return 成功/失敗(正常にファイルリストを取得できなかった場合)
     */
    virtual bool prevVolume()=0;
    /**
     * @brief on_ready アプリの準備が終わった段階で呼び出される。最初に、あるいは次に表示すべき画像およびそのファイルパスがemitされる
     */
    void on_ready();

signals:
    /**
     * @brief changing 次に表示すべき画像が通知される。View側はその画像を画面に表示すべきである
     */
    void changing(QImage image) const;
    /**
     * @brief changed 次に表示される画像のファイルパスが通知される。アプリ本体が情報を得るのはこのタイミング
     * @param path
     */
    void changed(QString path) const;
};

class FileVolumeArchive : public IFileVolume
{
public:
    /**
     * @brief 新しいアーカイブを設定する
     * @param dir
     */
    explicit FileVolumeArchive(QString archivePath);

    /**
     * @brief 現在のファイルリストの中で次のファイルに移動する
     * @return 成功/失敗(ファイルリスト終端等)
     */
    bool nextFile();
    /**
     * @brief 現在のファイルリストの中で前のファイルに移動する
     * @return 成功/失敗(ファイルリスト終端等)
     */
    bool prevFile();
    /**
     * @brief 現在のファイルリストの中で指定されたidx値に対応するファイルに移動する(最大値はディレクトリまたはアーカイブの画像数-1)
     * @return 成功/失敗(ファイルリスト終端等)
     */
    bool setIndexedFile(int idx);
    /**
     * @brief 次のディレクトリまたはアーカイブに移動する
     * @return 成功/失敗(正常にファイルリストを取得できなかった場合)
     */
    bool nextVolume();
    /**
     * @brief 前のディレクトリまたはアーカイブに移動する
     * @return 成功/失敗(正常にファイルリストを取得できなかった場合)
     */
    bool prevVolume();

    QString currentPath();
    QImage currentImage();

};



#endif // FILELIST_H
