
[![](https://img.shields.io/badge/VisualStudio-2017%20Community-ff69b4.svg)](https://docs.microsoft.com/ja-jp/visualstudio/releasenotes/vs2017-relnotes)
[![](https://img.shields.io/badge/DirectXSDK-June%202010-yellow.svg)](https://www.microsoft.com/en-us/download/details.aspx?id=6812)
[![](https://img.shields.io/badge/FBX%20SDK-2019.0VS2015-blue.svg)](https://www.autodesk.com/developer-network/platform-technologies/fbx-sdk-2019-2)
# Lonely

![Lonely イメージ画像](../../Pictures/Screenshots/lonelyImage.png)

ゲーム概要
---
プレイヤーは飼い主に置き忘れられたスマホ猫となる。
スマホアプリを駆使して、飼い主のもとへ帰ろう。

* #### プラットフォーム
  * Windows

* #### プレイ人数
  * 一人用


プロジェクトをビルドするための準備
---

Lonelyのプロジェクトをビルドするには必要なツールとsdkを用意する必要があります。

* 必要なツール
  * Visual Studio 2017  


* 必要なsdk  
  * Microsoft DirectX SDK (June 2010)  [こちら](https://www.microsoft.com/en-us/download/details.aspx?id=6812)  
    Microsoft DirectX SDkはダウンロードしたexeに従えば簡単にインストールできます。

  * Autodesk Fbxsdk(2019.0VS2015)  [こちら](https://www.autodesk.com/developer-network/platform-technologies/fbx-sdk-2019-2)  
    このプロジェクトが開始された際の最新fbxsdkバージョンが2019.0VS2015だったので、このプロジェクトでは2019.0VS2015で制作しています。
    こちらもダウンロードしたexeに従えばインストールできます。

    sdkをダウンロードしたら以下の環境変数を登録してください。  
    * FBXSDK_DIR  
      fbxsdkのディレクトリ  
      例 : C:\Program Files\Autodesk\FBX\FBX SDK\2019.0
