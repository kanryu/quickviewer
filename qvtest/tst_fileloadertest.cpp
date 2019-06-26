#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include "fileloader7zarchive.h"

#define DATAPATH "../../quickviewer/qvtest/data/"

/**
 * @brief The FileLoaderTest class
 *
 * zip loading check with FileLoader7zArchive.
 *
 * there are 4 test archive with 2 options
 * File name character encoding:
 *      mbcs:      no encoding, Depends on the system
 *      utf8:      encoding by UTF-8
 * File content codecs:
 *      deflate:   compression algorithm of regular zip archive
 *      deflate64: new algorithm added to recent zip archive
 */
class FileLoaderTest : public QObject
{
    Q_OBJECT

public:
    FileLoaderTest();

private Q_SLOTS:
    void testCase1_deflate_mbcs();
    void testCase2_deflate_utf8();
    void testCase3_deflate64_mbcs();
    void testCase4_deflate64_utf8();
};

FileLoaderTest::FileLoaderTest()
{
}

void FileLoaderTest::testCase1_deflate_mbcs()
{
    FileLoader7zArchive seven(nullptr, "zip", DATAPATH "deflate-mbcs.zip");
    Q_ASSERT(seven.volumePath() == DATAPATH "deflate-mbcs.zip");

    // check filelist
    QStringList files = seven.contents();
    Q_ASSERT(files.length() == 1);
    Q_ASSERT(QDir::fromNativeSeparators(files[0]) == "サンプルフォルダ/test.bmp");

    QMutex mutex;
    QByteArray bytes = seven.getFile(files[0], mutex);
    Q_ASSERT(bytes.length() == 1080054);
    QImage image = QImage::fromData(bytes, "bmp");
    Q_ASSERT(image.width() == 600);
}

void FileLoaderTest::testCase2_deflate_utf8()
{
    FileLoader7zArchive seven(nullptr, "zip", DATAPATH "deflate-utf8.zip");
    Q_ASSERT(seven.volumePath() == DATAPATH "deflate-utf8.zip");

    // check filelist
    QStringList files = seven.contents();
    Q_ASSERT(files.length() == 1);
    Q_ASSERT(QDir::fromNativeSeparators(files[0]) == "サンプルフォルダ/test.bmp");

    QMutex mutex;
    QByteArray bytes = seven.getFile(files[0], mutex);
    Q_ASSERT(bytes.length() == 1080054);
    QImage image = QImage::fromData(bytes, "bmp");
    Q_ASSERT(image.width() == 600);
}

void FileLoaderTest::testCase3_deflate64_mbcs()
{
    FileLoader7zArchive seven(nullptr, "zip", DATAPATH "deflate64-mbcs.zip");
    Q_ASSERT(seven.volumePath() == DATAPATH "deflate64-mbcs.zip");

    // check filelist
    QStringList files = seven.contents();
    Q_ASSERT(files.length() == 1);
    Q_ASSERT(QDir::fromNativeSeparators(files[0]) == "サンプルフォルダ/test.bmp");

    QMutex mutex;
    QByteArray bytes = seven.getFile(files[0], mutex);
    Q_ASSERT(bytes.length() == 1080054);
    QImage image = QImage::fromData(bytes, "bmp");
    Q_ASSERT(image.width() == 600);
}

void FileLoaderTest::testCase4_deflate64_utf8()
{
    FileLoader7zArchive seven(nullptr, "zip", DATAPATH "deflate64-utf8.zip");
    Q_ASSERT(seven.volumePath() == DATAPATH "deflate64-utf8.zip");

    // check filelist
    QStringList files = seven.contents();
    Q_ASSERT(files.length() == 1);
    Q_ASSERT(QDir::fromNativeSeparators(files[0]) == "サンプルフォルダ/test.bmp");

    QMutex mutex;
    QByteArray bytes = seven.getFile(files[0], mutex);
    Q_ASSERT(bytes.length() == 1080054);
    QImage image = QImage::fromData(bytes, "bmp");
    Q_ASSERT(image.width() == 600);
}

QTEST_MAIN(FileLoaderTest)

#include "tst_fileloadertest.moc"
