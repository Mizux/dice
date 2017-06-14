//! @file
#pragma once

#include <QComboBox>
#include <QPushButton>
#include <QSpinBox>
#include <QTableWidget>
#include <QWidget>

#include <Dice/Dice.hpp>
#include <Dice/Die.hpp>

class DiceWidget : public QWidget {
	Q_OBJECT

	public:
	DiceWidget(QWidget* parent = 0);
	virtual ~DiceWidget();
	DiceWidget(const DiceWidget&) = delete;
	DiceWidget& operator=(const DiceWidget&) = delete;
	DiceWidget(const DiceWidget&&)           = delete;
	DiceWidget& operator=(const DiceWidget&&) = delete;

	public slots:
	void calculateStat();
	void setTupleSize(int size);
	void setSideNumber(int size);

	private:
	//! @brief Minimum number of dice in the pool (default 6 dices)
	QSpinBox* _diceNumberMin;
	//! @brief Maximum number of dice in the pool (default 6 dices)
	QSpinBox* _diceNumberMax;

	//! @brief Use to define the number of side each die will have.
	//! @details Must in range [1,8] (default d6)
	QSpinBox* _dieSideNumber;
	QVector<QComboBox*> _dieSides;

	//! @brief Use to define the size of the Sequence.
	//! @details Must in range [1,4] (default 1)
	QSpinBox* _tupleSize;
	QVector<QComboBox*> _tupleSides;

	QPushButton* _calculateButton;
	QTableWidget* _result;

	void _setupWidget();
	//! @brief Create a ComboBox with all possible Face (Range [1,8], default 1).
	QComboBox* createFaceSelector();
	//! @brief Return a Die (i.e. know the die shape).
	Dice::Die getDie() const;
	//! @brief Return the Sequence to look for.
	Dice::FaceTuple getTuple() const;
};
