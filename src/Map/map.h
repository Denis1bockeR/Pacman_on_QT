#ifndef _MAP_H_
#define _MAP_H_

#include <utility>
#include <vector>
#include <array>

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QString>

#include "../Element/gameElement.h"

#define SIZE_SCORE 30

class GameWindow;

class Map : public QGraphicsScene
{
	Q_OBJECT

public:
	GameWindow* window;
public:
	enum Score { sGhost = 50, sBall = 10, sSuperBall = 30 };

	Map(const char* puth, ushort h, ushort w);
	~Map();

	void setScore(Score score) noexcept;

	void checkEndGameWin() noexcept;
	void endGameLose() noexcept;

	inline int getSizeOtherEl() noexcept { return otherElement.size(); };
	inline OtherElement* getOneOtherEl(short x, short y) const noexcept { return otherElement[y][x]; };
	inline Pacman* getPacman() noexcept { return &pacman; };
	inline Ghost*  getGhost(short i)  noexcept { return &ghost[i]; };

	inline ushort getNumBall() noexcept { return nBall; };
	inline ushort getOriginalNumBall() noexcept { return originalNumBall; };

	inline std::pair<short, short> getGhastPos() noexcept { return{ X_GHAST, Y_GHAST }; };

	inline void updateDispScore() noexcept { dispScore->setPlainText("Score: " + QString::number(score)); };
	inline ushort getScore() noexcept { return score; };
private:
	ushort weight, height, score, nBall, originalNumBall;
	short  X_GHAST, Y_GHAST;

	QGraphicsTextItem* dispScore;
	std::vector <std::vector<OtherElement*>> otherElement;
	Pacman pacman;
	std::array<Ghost, 4> ghost;

	friend class GameElement;
	friend class GameWindow;
private:
	void readMap(const char* puth);
	void setOtherElAttribute(OtherElement::ElementType type, QPixmap pix, short mapPosX, short mapPosY, short x, short y) noexcept;

	void displayScore() noexcept;
	void updateMapDepenScore();
};

#endif // !_MAP_H_
