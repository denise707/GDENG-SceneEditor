#pragma once
#include <iostream>
#include <vector>
#include <stack>

class EditorAction;
class AGameObject;
class ActionHistory
{
public:
	typedef std::stack<EditorAction*> ActionStack;
	static ActionHistory* getInstance();
	static void initialize();
	static void destroy();

	void recordAction(AGameObject* gameObject);
	bool hasRemainingUndoActions();
	bool hasRemainingRedoActions();
	EditorAction* undoAction();
	EditorAction* redoAction();
	void clear();

private:
	ActionHistory();
	~ActionHistory();
	ActionHistory(ActionHistory const&) {};            
	ActionHistory& operator=(ActionHistory const&) {}; 

	static ActionHistory* sharedInstance;

	ActionStack actionsPerformed;
	ActionStack actionsCancelled;

	void AddActionToStack(EditorAction* action);

};
