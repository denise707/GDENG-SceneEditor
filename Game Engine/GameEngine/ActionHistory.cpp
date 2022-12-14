#include "ActionHistory.h"
#include "EditorAction.h"
#include "EngineBackend.h"

ActionHistory* ActionHistory::sharedInstance = NULL;

ActionHistory* ActionHistory::getInstance()
{
	return sharedInstance;
}

void ActionHistory::initialize()
{
	sharedInstance = new ActionHistory();
}

void ActionHistory::destroy()
{
	delete sharedInstance;
}

void ActionHistory::recordAction(AGameObject* gameObject)
{
	// only save editor action when in editor state
	if (EngineBackend::getInstance()->getMode() == EngineBackend::EditorMode::EDITOR) 
	{
		// create action
		EditorAction* action = new EditorAction(gameObject);
		// add action to stack
		AddActionToStack(action);
	}
}

bool ActionHistory::hasRemainingUndoActions()
{
	if (this->actionsPerformed.empty())
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool ActionHistory::hasRemainingRedoActions()
{
	if (this->actionsCancelled.empty())
	{
		return false;
	}
	else
	{
		return true;
	}
}


EditorAction* ActionHistory::undoAction()
{
	//only perform in editor state
	if (EngineBackend::getInstance()->getMode() == EngineBackend::EditorMode::EDITOR) 
	{
		if (this->hasRemainingUndoActions())
		{
			//LAST IN FIRST OUT
			// get the last in (last action)
			EditorAction* action = this->actionsPerformed.top();
			// remove the last in from top
			this->actionsPerformed.pop(); 
			// add to cancelled actions stack
			this->actionsCancelled.push(action);
			return action;
		}
		else
		{
			std::cout << "No remaining undos. \n";
			return nullptr;
		}
	}
	else
	{
		return nullptr;
		std::cout << "UNDO is ONLY AVAILABLE during EDITING STATE \n";

	}

	
}

EditorAction* ActionHistory::redoAction()
{
	//do not undo actions during play mode.
	if (EngineBackend::getInstance()->getMode() == EngineBackend::EditorMode::EDITOR) {
		if (this->hasRemainingRedoActions())
		{
			// get top
			EditorAction* action = this->actionsCancelled.top();
			// remove top
			this->actionsCancelled.pop();
			// add to actions performed stack
			this->actionsPerformed.push(action);

			return action;
		}
		else
		{
			std::cout << "REDO is ONLY AVAILABLE during EDITING STATE \n";
			return nullptr;
		}
	}
	else
	{
		return nullptr;
	}

	
}

void ActionHistory::clear()
{
	for (int i = 0; i< actionsPerformed.size(); i++)
	{
		EditorAction* action = this->actionsPerformed.top();
		delete action;
		this->actionsPerformed.pop();
	}

	for (int i = 0; i < actionsCancelled.size(); i++)
	{
		EditorAction* action = this->actionsCancelled.top();
		delete action;
		this->actionsCancelled.pop();
	}
}

ActionHistory::ActionHistory()
{
}

ActionHistory::~ActionHistory()
{
	this->clear();
}

void ActionHistory::AddActionToStack(EditorAction* action)
{
	this->actionsPerformed.push(action);
	cout << " new action performed by: " + action->getName()+"\n";
}