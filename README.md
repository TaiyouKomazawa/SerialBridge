# SerialBridge (for SPI)
##  概要
本ライブラリは、PC(MCP2210)とSTM32-MCUをSPIで接続する目的でフォーク・変更されました。   
1対1全二重シリアル通信により通信の高速化、安定化を図っています。    

## リリースバージョン

* **1.0.0**

## サブモジュール
- kerrydwong/MCP2210-Library    
https://github.com/kerrydwong/MCP2210-Library.git

## 開発環境
- Ubuntu 20.04 LTS
- C++11 (GNU GCC 10.3.0)
- STM32CubeIDE 1.7.0 HAL API

## Commit Prefix
|Prefix   |内容     |
|---------|--------|
|[Add]    |ファイル追加 / 機能追加|
|[Delete] | ファイル削除 / 機能削除|
|[Update] | 機能修正 (バグ修正を除く)|
|[Fix]    |バグ修正|
|[HotFix] |クリティカルなバグ修正|
|[Clean]  |リファクタリング / コード整理|
|[Change] | 仕様変更|
|[Rename] | 名前変更|
|[Docs] | ドキュメント(説明)系の編集|
|[Debug] | デバッグコードに関する編集 |

## License
Apache-2.0 License

## Developer
- [testusuke](https://github.com/testusuke) (Original repository maintainer)
- [TaiyouKomazawa](https://github.com/TaiyouKomazawa)
