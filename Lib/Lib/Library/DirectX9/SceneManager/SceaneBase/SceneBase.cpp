#include"SceneBase.h"

SceneBase::SceneBase(int _sceneID) :
	m_State(INIT_STATE)
	,m_SceneID(_sceneID)
{
}

SceneBase::~SceneBase()
{
}

bool SceneBase::Initialize()
{
	return  true;
}

void SceneBase::Finalize()
{

}

void SceneBase::Update()
{

}