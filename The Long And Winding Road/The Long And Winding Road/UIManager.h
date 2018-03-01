#ifndef UIMANAGER_H
#define UIMANAGER_H

enum NUMBER_OF_ATTACKS
{
	ATK_0,
	ATK_1,
	ATK_2,
	ATK_3,
	ATK_4,
	ATK_MAX,

};

class UIManager
{
public:
	UIManager();
	~UIManager();
	void Draw();
	void Control();
private:

};

#endif