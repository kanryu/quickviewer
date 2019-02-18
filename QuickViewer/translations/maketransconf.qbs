import qbs
import "../src/qlanguageselector/modules/transconf/TransConfProduct.qbs" as TransConfProduct


Project {
    name: "QuickViewer" // you application name
    property string version: "1.1.3" // your application version
    property string confExt: ".txt" // file extent of your conf type translation files, usually ".lang", ".lng", ".txt" or ".ini"
//    property string targetInstallDir: qbsbuildconfig.appInstallDir

    qbsSearchPaths: base.concat(["../src/qlanguageselector"])
    Product {
        name: "List up translations"
        Group {
            files: [
                "*.ts",
            ]
            fileTags: ["ts_input"]
        }
    }
    Product {
        name: "Make user language translation"
        Group {
            files: ["quickviewer_ja.ts"]
            fileTags: ["ts_default_input"]
        }
    }
    Product {
        name: "Make the reverse translation"
        Group {
            files: ["quickviewer_ja.ts"]
            fileTags: ["ts_reverse_input"]
        }
    }
    TransConfProduct {
        name: "Generating TransConfs"
        type: ["Conf type translations"]
        version: project.version
        confExt: project.confExt
        template: {
            return {
                file_header: [
                    "; Language file was generated at "+transconf.Generator.toMailDateString(new Date(Date.now())),
                    "; === COMMENTS ===",
                    "; This is a language file for "+project.name+". Lines beginning with ; are comments.",
                    "; Each language should have one language file in UTF-8 character set.",
                    "; When you change the text of this file, the notation of the application will be changed.",
                    "; If you make a new translation or modify an existing one,",
                    "; please post to Issue(https://github.com/kanryu/quickviewer/issues) or send an email to <k.kanryu@gmail.com>.",
                    "; ",
                    "; Note 1: Use \\n (backslash+n) instead of new line for each text, if you need.",
                    "; Note 2: 'hint' is a hint comment for each 'text'.",
                    "; ",
                ],
                section_name: "FileInfo",
                entries: {
                    "quickviewer_ja.ts": {
                        TranslatorName: "QuickViewer Developer Team",
                        TranslatorEmail: "k.kanryu@gmail.com",
                        Caption: "Japanese",
                        LanguageName: "日本語",
                        LanguageCode: "ja",
                        TargetVersion: version,
                    },
                    "quickviewer_es.ts": {
                        TranslatorName: "QuickViewer Developer Team",
                        TranslatorEmail: "k.kanryu@gmail.com",
                        Caption: "Spanish",
                        LanguageName: "Spanish",
                        LanguageCode: "es",
                        TargetVersion: version,
                    },
                    "quickviewer_zh.ts": {
                        TranslatorName: "河海江超群",
                        TranslatorEmail: "mcoder2014@sina.com",
                        Caption: "Chinese",
                        LanguageName: "Chinese(zh_CN)",
                        LanguageCode: "zh",
                        TargetVersion: version,
                    },
                    "quickviewer_el.ts": {
                        TranslatorName: "Edgar Hoffmann",
                        TranslatorEmail: "kontakt@freiesoftwareog.org",
                        Caption: "Greek",
                        LanguageName: "Greek",
                        LanguageCode: "el",
                        TargetVersion: version,
                    },
                    "quickviewer_fr.ts": {
                        TranslatorName: "michel-wf",
                        TranslatorEmail: "michel.2wf@sfr.fr",
                        Caption: "French",
                        LanguageName: "French",
                        LanguageCode: "fr",
                        TargetVersion: version,
                    },
                }
            }
        }

//        tsFileNameMap: { // if you want to change the file name of conf type translations, define the mapping
//            return {
//                "quickviewer_ja.ts": "aaa.txt",
//            }
//        }

        Depends { name: "List up translations" }
    }
    TransConfProduct {
        name: "Generating Default TransConfs"
        type: ["Default(User Language) translation"]
        version: project.version
        confExt: project.confExt
        template: {
            return {
                file_header: [
                    "; Language file was generated at "+transconf.Generator.toMailDateString(new Date(Date.now())),
                    "; === COMMENTS ===",
                    "; This is a language file for "+project.name+". Lines beginning with ; are comments.",
                    "; Each language should have one language file in UTF-8 character set.",
                    "; ",
                    "; You can edit this file with a text editor.",
                    "; Rewriting 'text' to **YOUR LANGUAGE**, you can translate QuickViewer.",
                    "; If you do, please do post it to us. Many other people will be able to use your translation.",
                    "; You can post to Issue(https://github.com/kanryu/quickviewer/issues) or send an email to <k.kanryu@gmail.com>.",
                    "; ",
                    "; Note 1: Use \\n (backslash+n) instead of new line for each text, if you need.",
                    "; Note 2: 'hint' is a hint comment for each 'text'.",
                    "; ",
                ],
                section_name: "FileInfo",
                entries: {
                    "quickviewer_ja.ts": {
                        Caption: "Your Language",
                        LanguageCode: "user",
                        TargetVersion: version,
                        TranslatorName: "YOUR NAME(edit it)",
                        TranslatorEmail: "YOUR EMAIL(edit it)",
                        LanguageName: "YOUR LANGUAGE(edit it)",
                    },
                }
            }
        }

        tsFileNameMap: { // if you want to change the file name of conf type translations, define the mapping
            return {
                "quickviewer_ja.ts": "YourLanguage.txt",
            }
        }

        Depends { name: "Make user language translation" }
    }
    TransConfProduct {
        name: "Generating Reverse TransConf"
        type: ["Reverse translation"]
        version: project.version
        confExt: project.confExt
        template: {
            return {
                file_header: [
                    "; The reverse language file was generated at "+transconf.Generator.toMailDateString(new Date(Date.now())),
                    "; === COMMENTS ===",
                    "; DO NOT EDIT THE FILE",
                    "; ",
                ],
            }
        }
        Depends { name: "Make the reverse translation" }
    }
}
