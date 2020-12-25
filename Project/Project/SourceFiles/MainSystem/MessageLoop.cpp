/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[MessageLoop.cpp] メッセージループクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：メッセージループクラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../StdAfx.h"
#include "MessageLoop.h"
#include "IManager.h"
#include "Manager/ApplicationManager.h"
#include "Manager/SplashScreenManager.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
MessageLoop::MessageLoop(IManager* iManager)
	: i_manager_(nullptr)
{
	i_manager_ = iManager;
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
MessageLoop::~MessageLoop()
{
	SAFE_DELETE_(i_manager_);
}

/*-----------------------------------------------------------------------------
/* ファクトリメソッド
-----------------------------------------------------------------------------*/
MessageLoop* MessageLoop::Create(MessageLoopType msgLoopTyep, const WindowStyle& windowStyle)
{
	switch (msgLoopTyep)
	{
	case MessageLoopType::SplashScreenWindow:
		return NEW MessageLoop(NEW SplashScreenManager(windowStyle));
	
	case MessageLoopType::ApplicationWindow:
		return NEW MessageLoop(NEW ApplicationManager(windowStyle));

	default:
		assert(!"不正なメッセージループの生成を検知!");
		break;
	}

	return nullptr;
}

/*-----------------------------------------------------------------------------
/* 起動処理
-----------------------------------------------------------------------------*/
bool MessageLoop::StartUp(void)
{
	if (i_manager_ == nullptr) { return false; }
	return i_manager_->Init();;
}

/*-----------------------------------------------------------------------------
/* 実行処理
-----------------------------------------------------------------------------*/
void MessageLoop::Run(void)
{
	MSG	  msg;								//ウィンドウプロシージャへのハンドラ
	DWORD execute_last_time = 0UL;			//1フレーム前の終了時間
	DWORD current_time		= 0UL;			//現在の時間
	DWORD ticks_counts		= 0UL;			//1フレームの経過時間

	const float maximum_delta_time = 0.05f;	//deltaTimeの最大制限値
	float		delta_time		   = 0.f;	//1フレーム前との差分の秒数		

	timeBeginPeriod(1); //分解能を設定

	for (;;)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			//ウィンドウメッセージ処理 
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//60fps化
			current_time = timeGetTime(); //実行時間を取得

			//1フレーム前との差分を取得
			ticks_counts = (current_time - execute_last_time);

			//秒数に変換
			delta_time = ((float)ticks_counts / 1000.f);

			if (delta_time >= (1 / 60))
			{
				//delta_time >= (1 / 60)
				//1フレーム前との差分が0.016...ミリ秒以上だったら実行する

				//delta_timeの制限
				//実行中やブレークポイント発行時等の予防措置
				if (delta_time >= maximum_delta_time)
				{
					delta_time = maximum_delta_time;
				}

				//nullチェック
				if (i_manager_ != nullptr)
				{
					i_manager_->Input();
					i_manager_->Update(delta_time);
					i_manager_->GenerateOutput();
				}

				//現在のフレームの実行前時間に実行後時間を代入。
				execute_last_time = current_time;
			}
		}
		const bool  lb = i_manager_->IsLoopBreak();
		const bool  sd = i_manager_->IsShutDown();

		if ((msg.message == WM_QUIT)|| lb || sd) { break; }
	}

	timeEndPeriod(1); //分解能を解除
}

/*-----------------------------------------------------------------------------
/* 停止処理
-----------------------------------------------------------------------------*/
void MessageLoop::ShutDown(void)
{
	i_manager_->Uninit();
}

/*-----------------------------------------------------------------------------
/* 停止処理
-----------------------------------------------------------------------------*/
Vector2* MessageLoop::GetSelectedAspectRatio(void)
{
	if (i_manager_ == nullptr) { return nullptr; }
	return i_manager_->GetSelectedAspectRatio();
}

/*-----------------------------------------------------------------------------
/* シャットダウンをするか
-----------------------------------------------------------------------------*/
bool MessageLoop::IsShutDown(void)
{
	if (i_manager_ == nullptr) { return false; }
	return i_manager_->IsShutDown();
}

/*-----------------------------------------------------------------------------
/* ループを脱出するか
-----------------------------------------------------------------------------*/
bool MessageLoop::IsLoopBreak(void)
{
	if (i_manager_ == nullptr) { return false; }
	return i_manager_->IsLoopBreak();
}

/*=============================================================================
/*		End of File
=============================================================================*/