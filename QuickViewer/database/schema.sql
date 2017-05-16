PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;

CREATE TABLE [t_version] ( --version
    [id] INTEGER PRIMARY KEY AUTOINCREMENT,
    [version] INTEGER NOT NULL, --version as integer MjMnPt
    [description] TEXT,
    [created_at] DATETIME
);

INSERT INTO t_version (version,description,created_at)
    VALUES (604, 'Database for thumbnails of Digital Books', datetime('2017-05-13 17:31:15'));



CREATE TABLE [t_thumbnails] ( --サムネイル
    [id] INTEGER PRIMARY KEY AUTOINCREMENT,
    [width] INTEGER NOT NULL, --サムネイルの幅
    [height] INTEGER NOT NULL, --サムネイルの高さ
    [thumbnail] BLOB, --JPEGのバイナリ
    [created_at] DATETIME
);

CREATE TABLE [t_catalogs] ( --カタログ
    [id] INTEGER PRIMARY KEY AUTOINCREMENT,
    [basevolume_id] INTEGER, -- カタログの基底となる [t_volumes].[id]
    [name] TEXT, --カタログの名称
    [path] TEXT, --カタログの基底フォルダパス
    [description] TEXT, --カタログの説明
    [created_at] DATETIME,
    [updated_at] DATETIME
);

CREATE TABLE [t_volumes] ( --ボリューム(フォルダまたはアーカイブ)
    [id] INTEGER PRIMARY KEY AUTOINCREMENT,
    [name] TEXT, --表示用のタイトル((タグ)要素は取り除かれるものとする)
    [realname] TEXT NOT NULL, --フォルダ名またはアーカイブのファイル名
    [path] TEXT NOT NULL, --ボリュームの存在箇所をフルPATHで
    [frontpage_id] INTEGER, -- 表紙となる [t_files].[id]
    [thumb_id] INTEGER, -- 表紙となる[t_thumbnails].[id]
    [parent_id] INTEGER, -- 自身の親となる [t_volumes].[id]。 NULLの場合もある
    [catalog_id] INTEGER -- 自身が含まれるcatalogの [t_catalogs].[id]
);

CREATE TABLE [t_files] ( --画像ファイル
    [id] INTEGER PRIMARY KEY AUTOINCREMENT,
    [volume_id] INTEGER, -- 自身が含まれているvolumeの[t_volumes].[id]
    [name] TEXT NOT NULL, -- ファイル名
    [size] INTEGER, -- ファイルサイズ
    [width] INTEGER,
    [height] TEXT,
    [thumb_id] INTEGER, -- このレコードの画像のサムネイルID
    [paper] TEXT, -- (オプション)白紙などを挿入する際などに使用
    [created_at] DATETIME,
    [updated_at] DATETIME,
    [alternated] BLOB -- (オプション)この画像の読み込みに時間がかかる場合の代替画像。
);

CREATE TABLE [t_tags] ( --タグ定義
    [id] INTEGER PRIMARY KEY AUTOINCREMENT,
    [name] TEXT NOT NULL, -- ファイル名
    [type_id] INTEGER -- (0:Normal, 1:Publisher(Author), 2:Publisher, 3:Author, 4:Rate)
);

CREATE TABLE [t_volumetags] (--ボリュームごとのタグ
    [volume_id] INTEGER NOT NULL, -- タグが含まれているvolumeの[t_volumes].[id]
    [tag_id] INTEGER NOT NULL,
    [catalog_id] INTEGER NOT NULL -- タグが含まれているvolumeが登録されたcatalogの[t_catalogs].[id]
);

CREATE TABLE [t_volumeorders] ( --ボリューム並べ替え順
    [id] INTEGER, -- [t_volumes].[id]
    [parent_id] INTEGER,
    [volumename_asc] INTEGER, -- ボリューム名をOS準拠で並べ替えた際の昇順の序数
    PRIMARY KEY(id)
);

/* ファイル情報を残して順序だけ入れ替えたい場合に一括でDROPして差し替えたほうが楽なため別テーブルにしておく */
CREATE TABLE [t_fileorders] ( --ファイル名並べ替え順
    [id] INTEGER, -- [t_files].[id]
    [volume_id] INTEGER,
    [filename_asc] INTEGER, -- ファイル名をOS準拠で並べ替えた際の昇順の序数
    PRIMARY KEY(id)
);

DELETE FROM sqlite_sequence;
INSERT INTO sqlite_sequence VALUES('t_thumbnails',0);
INSERT INTO sqlite_sequence VALUES('t_catalogs',0);
INSERT INTO sqlite_sequence VALUES('t_volumes',0);
INSERT INTO sqlite_sequence VALUES('t_tags',0);
INSERT INTO sqlite_sequence VALUES('t_files',0);

CREATE INDEX [i_volumes_by_path] On [t_volumes]([path] ASC);
CREATE INDEX [i_volumes_by_parent_id] On [t_volumes]([parent_id]);
CREATE INDEX [i_volumes_by_catalog_id] On [t_volumes]([catalog_id]);
CREATE INDEX [i_volumetags] On [t_volumetags]([volume_id],[tag_id],[catalog_id]);
CREATE INDEX [i_files_by_volume_id] On [t_files]([volume_id]);
CREATE INDEX [i_volumeorders_by_parentid_volumenameasc] ON [t_volumeorders] ([parent_id] ,[volumename_asc] ASC);
CREATE INDEX [i_fileorders_by_volumeid_filenameasc] ON [t_fileorders] ([volume_id] ,[filename_asc] ASC);

CREATE VIEW [v_filethmasc] AS 
SELECT 
    [t_files].[id] AS [id],
    [t_files].[volume_id] AS [volume_id], -- 自身が含まれているvolumeの[t_volumes].[id]
    [t_files].[name] AS [name], -- ファイル名
    [t_fileorders].[filename_asc] AS [filename_asc], --ファイル名をOS準拠で並べ替えた際の昇順の序数
    [t_files].[size] AS [size], -- ファイルサイズ
    [t_files].[width] AS [width],
    [t_files].[height] AS [height],
    [t_thumbnails].[thumbnail] AS [thumbnail], -- JPEGのバイナリ
    [t_files].[created_at] AS [created_at],
    [t_files].[updated_at] AS [updated_at],
    [t_files].[alternated] AS [alternated] -- (オプション)この画像の読み込みに時間がかかる場合の代替画像。
FROM [t_files], [t_thumbnails], [t_fileorders]
WHERE [t_files].[thumb_id] = [t_thumbnails].[id]
  AND [t_files].[id] = [t_fileorders].[id] 
ORDER BY [t_fileorders].[filename_asc] ASC
;
CREATE VIEW [v_volumethm] AS 
SELECT 
    [t_volumes].[id] AS [id],
    [t_volumes].[name] AS [name], -- 表示用のタイトル
    [t_volumes].[realname] AS [realname], -- フォルダ名またはアーカイブのファイル名
    [t_volumeorders].[volumename_asc] AS [realname_asc], --ファイル名をOS準拠で並べ替えた際の昇順の序数
    [t_volumes].[path] AS [path], -- ボリュームの存在箇所をフルPATHで
    [t_volumes].[frontpage_id] AS [frontpage_id], -- 表紙となる [t_files].[id]
    [t_volumes].[parent_id] AS [parent_id], -- 自身の親となる [t_volumes].[id]。 NULLの場合もある
    [t_thumbnails].[thumbnail] AS [thumbnail] -- JPEGのバイナリ
FROM ([t_volumes] LEFT OUTER JOIN [t_thumbnails] 
    ON [t_volumes].[thumb_id] = [t_thumbnails].[id]) 
INNER JOIN [t_volumeorders]
    ON [t_volumes].[id] = [t_volumeorders].[id] 
ORDER BY [t_volumeorders].[volumename_asc] ASC
;
CREATE VIEW [v_volumethm_by_parentpath] AS 
SELECT 
    [v_volumethm].[id] AS [id],
    [v_volumethm].[name] AS [name], -- 表示用のタイトル
    [v_volumethm].[realname] AS [realname], -- フォルダ名またはアーカイブのファイル名
    [v_volumethm].[realname_asc] AS [realname_asc], --ファイル名をOS準拠で並べ替えた際の昇順の序数
    [v_volumethm].[path] AS [path], -- ボリュームの存在箇所をフルPATHで
    [v_volumethm].[frontpage_id] AS [frontpage_id], -- 表紙となる [t_files].[id]
    [v_volumethm].[parent_id] AS [parent_id], -- 自身の親となる [t_volumes].[id]。 NULLの場合もある
    [v_volumethm].[thumbnail] AS [thumbnail], -- JPEGのバイナリ
    [t_volumes].[path] AS [parentpath] -- ボリュームの存在箇所をフルPATHで
FROM [v_volumethm], [t_volumes]
WHERE [v_volumethm].[parent_id] = [t_volumes].[id]
ORDER BY [v_volumethm].[realname_asc] ASC
;
CREATE VIEW [v_tags_by_count] AS 
SELECT t.id, t.name, t.type_id, v2.cnt
FROM t_tags t INNER JOIN (SELECT COUNT(*) as cnt, v.tag_id FROM t_volumetags v GROUP BY v.tag_id) v2 
    ON v2.tag_id = t.id ORDER BY v2.cnt DESC
;

COMMIT;
