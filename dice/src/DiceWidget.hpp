//! @file
#pragma once

#include <QComboBox>
#include <QPushButton>
#include <QSpinBox>
#include <QTableWidget>
#include <QWidget>

#include <Dice/Dice.hpp>
#include <Dice/Die.hpp>

//! @brief Widget use to calculate and display FaceTuple probability.
class DiceWidget : public QWidget {
	Q_OBJECT

	public:
	//! @brief Default Ctor.
	//! @param[in] parent Parent widget if any.
	DiceWidget(QWidget* parent = 0);
	//! @brief Default Dtor.
	virtual ~DiceWidget();
	//! @brief Remove copy Ctor.
	DiceWidget(const DiceWidget&) = delete;
	//! @brief Remove copy operator.
	//! @return This instance.
	DiceWidget& operator=(const DiceWidget&) = delete;
	//! @brief Remove move Ctor.
	DiceWidget(const DiceWidget&&) = delete;
	//! @brief Remove move operator.
	//! @return This instance.
	DiceWidget& operator=(const DiceWidget&&) = delete;

	public slots:
	//! @brief Compute statistic for the current configuration.
	void calculateStat();
	//! @brief Modifies the size of the Face Tuple.
	//! @param[in] size The number of Face whose the tuple is composed.
	void setTupleSize(int size);
	//! @brief Modifies the number of Face each Die will contain.
	//! @param[in] size The number of Face whose the Die is composed.
	void setSideNumber(int size);

	private:
	//! @brief Minimum number of dice in the pool (default 6 dices)
	QSpinBox* _diceNumber;

	//! @brief Use to define the number of side each Die will have.
	//! @details Must in range [1,8] (default d6)
	QSpinBox* _dieSideNumber;
	//! @brief Container used to store the value of each Face of the Die.
	QVector<QComboBox*> _dieSides;

	//! @brief Use to define the size of the Sequence.
	//! @details Must in range [1,4] (default 1)
	QSpinBox* _tupleSize;
	//! @brief Container used to store the value of each Face of the tuple.
	QVector<QComboBox*> _tupleSides;

	//! @brief Button used to trig the computation.
	QPushButton* _calculateButton;
	//! @brief Widget use to display the result of the computation.
	QTableWidget* _result;

	//! @brief Internal function used to build the widget and its components.
	void _setupWidget();
	//! @brief Create a ComboBox with all possible Face (Range [1,8], default 1).
	//! @return The newly created QComboBox.
	QComboBox* createFaceSelector();
	//! @brief Return a Die (i.e. know the die shape).
	//! @return The Die currently in use.
	Dice::Die getDie() const;
	//! @brief Return the Sequence to look for.
	//! @return The FaceTuple currently in use.
	Dice::FaceTuple getTuple() const;
};
