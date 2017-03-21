#ifndef FILEVOLUMEZIPARCHIVE_H
#define FILEVOLUMEZIPARCHIVE_H

#include <QObject>
#include <QtGui/5.7.0/QtGui/private/qzipreader_p.h>
#include "filevolume.h"

class FileVolumeZipArchive : public IFileVolume
{
    Q_OBJECT
public:
    /**
     * @brief 新しいディレクトリを設定する
     * @param dir
     */
    explicit FileVolumeZipArchive(QObject* parent, QString zippath);

    QString currentPath();
    QPixmap currentImage();

public:
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
     * @brief ボリュームが持つページ数を返す
     * @return ボリュームが持つページ数
     */
    int size();

protected:
    QString m_zipfilepath;
    QZipReader m_reader;
    QList<QString> m_filelist;
    /**
     * @brief m_current　現在選択中のファイル名
     */
    QString m_current;
    /**
     * @brief m_cachedPath キャッシュされた現在の画像のファイルパス
     */
    QString m_cachedPath;
    /**
     * @brief m_cachedImage キャッシュされた現在の画像
     */
    QPixmap m_cachedImage;
};

#endif // FILEVOLUMEZIPARCHIVE_H
