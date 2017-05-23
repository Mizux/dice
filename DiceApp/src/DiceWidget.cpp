//! @file

#include "DiceWidget.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QSpacerItem>
#include <QVBoxLayout>
#include <cassert>
#include <iostream>
#include <numeric>

#include <Dice/Roll.hpp>
#include <Dice/Stat.hpp>

DiceWidget::DiceWidget(QWidget* parent)
  : QWidget(parent) {
	_setupWidget();
}

DiceWidget::~DiceWidget() {}

void
DiceWidget::calculateStat() {
	{ // Clear Table...
		_result->setRowCount(0);
		_result->setColumnCount(4);
		_result->setSortingEnabled(false);
		QStringList headers;
		headers.append("Dices Number");
		headers.append("Tuples Number");
		headers.append("Exactly");
		headers.append("Cumulative");
		_result->setHorizontalHeaderLabels(headers);
	}

	// For each number of die possible.
	for (std::size_t diceNumber = std::size_t(_diceNumberMin->value());
	     diceNumber <= std::size_t(_diceNumberMax->value());
	     ++diceNumber) {
		Dice::Die die = getDie();
		// std::cerr << "Die: " << die << std::endl;
		Dice::FaceTuple tuple = getTuple();
		// std::cerr << "Tuple: " << tuple << std::endl;
		Dice::Dice dice(diceNumber, die);
		// TupleStat stat = dice.getTupleStat(tuple);

		// 2) Display results
		/*
		for (std::size_t tupleNumber = 0; tupleNumber < stat.size(); ++tupleNumber) {
			_result->insertRow(0);
			_result->setItem(0, 0, new QTableWidgetItem(QString::number(diceNumber)));
			_result->setItem(0, 1, new QTableWidgetItem(QString::number(tupleNumber)));
			_result->setItem(0, 2, new QTableWidgetItem(QString::number(stat[tupleNumber])));
			double accumulation = 0;
			for (std::size_t i = tupleNumber; i < stat.size(); ++i) {
				accumulation += stat[i];
			}
			_result->setItem(0, 3, new QTableWidgetItem(QString::number(accumulation)));
		}
		*/
	}
	_result->setSortingEnabled(true);
}

void
DiceWidget::setTupleSize(int size) {
	for (int i = 0; i < _tupleSides.size(); ++i) {
		if (i < size)
			_tupleSides[i]->show();
		else
			_tupleSides[i]->hide();
	}
}

void
DiceWidget::setSideNumber(int size) {
	for (int i = 0; i < _dieSides.size(); ++i) {
		if (i < size)
			_dieSides[i]->show();
		else
			_dieSides[i]->hide();
	}
}

// Qt don't like signal overload (e.g. QSpinBox::valueChanged(int) and
// QSpinBox::valueChanged(string))
template <typename... Args>
struct OVERLOAD {
	template <typename C, typename R>
	static constexpr auto of(R (C::*PMF)(Args...)) -> decltype(PMF) {
		return PMF;
	}
};

void
DiceWidget::_setupWidget() {
	setObjectName("Dice");
	setLayout(new QVBoxLayout(this));

	{ // Dice Number & Shape
		QHBoxLayout* box = new QHBoxLayout();
		layout()->setAlignment(box, Qt::AlignLeft);

		QLabel* diceNumber = new QLabel("DiceNumber: ", this);
		diceNumber->setFixedSize(diceNumber->sizeHint());
		box->addWidget(diceNumber);

		_diceNumberMin = new QSpinBox(this);
		_diceNumberMin->setValue(6);
		_diceNumberMin->setRange(1, 12);
		box->addWidget(_diceNumberMin);

		_diceNumberMax = new QSpinBox(this);
		_diceNumberMax->setValue(6);
		_diceNumberMax->setRange(1, 12);
		box->addWidget(_diceNumberMax);

		QLabel* dieSide = new QLabel("side: ", this);
		dieSide->setFixedSize(dieSide->sizeHint());
		box->addWidget(dieSide);

		_dieSideNumber = new QSpinBox(this);
		_dieSideNumber->setValue(6);
		_dieSideNumber->setRange(1, 8);
		box->addWidget(_dieSideNumber);
		connect(_dieSideNumber,
		        OVERLOAD<int>::of(&QSpinBox::valueChanged),
		        this,
		        &DiceWidget::setSideNumber);

		for (int i = 0; i < 8; ++i) {
			_dieSides.append(createFaceSelector());
			_dieSides.back()->setCurrentIndex(i);
			if (i > 5) _dieSides.back()->hide();
			box->addWidget(_dieSides.back());
		}

		box->addItem(
		  new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum));

		layout()->addItem(box);
	}
	{ // Sequence to Search
		QHBoxLayout* box = new QHBoxLayout();
		layout()->setAlignment(box, Qt::AlignLeft);

		QLabel* sequenceSize = new QLabel("Tuple Size:", this);
		sequenceSize->setFixedSize(sequenceSize->sizeHint());
		box->addWidget(sequenceSize);

		_tupleSize = new QSpinBox(this);
		_tupleSize->setRange(1, 4);
		_tupleSize->setValue(1);
		box->addWidget(_tupleSize);
		connect(_tupleSize,
		        OVERLOAD<int>::of(&QSpinBox::valueChanged),
		        this,
		        &DiceWidget::setTupleSize);

		QLabel* sequence = new QLabel("Tuple:", this);
		sequence->setFixedSize(sequence->sizeHint());
		box->addWidget(sequence);

		for (int i = 0; i < 4; ++i) {
			_tupleSides.append(createFaceSelector());
			_tupleSides.back()->setCurrentIndex(i);
			if (i > 0) _tupleSides.back()->hide();
			box->addWidget(_tupleSides.back());
		}

		box->addItem(
		  new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum));

		layout()->addItem(box);
	}
	{ // Calculate button
		_calculateButton = new QPushButton("Calculate", this);
		layout()->addWidget(_calculateButton);
		// layout()->setAlignment(_calculateButton, Qt::AlignCenter);
		connect(
		  _calculateButton, &QPushButton::clicked, this, &DiceWidget::calculateStat);
	}
	{ // Result Widget
		QHBoxLayout* box = new QHBoxLayout();

		box->addItem(new QSpacerItem(
		  0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));

		_result = new QTableWidget(this);
		//_result->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		box->addWidget(_result);

		box->addItem(new QSpacerItem(
		  0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));

		layout()->addItem(box);
	}

	QSpacerItem* spacer =
	  new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
	layout()->addItem(spacer);
}

QComboBox*
DiceWidget::createFaceSelector() {
	QComboBox* selector = new QComboBox(this);
	//! @todo Add Icon for each face !
	selector->addItem("One", 1);
	selector->addItem("Two", 2);
	selector->addItem("Three", 3);
	selector->addItem("Four", 4);
	selector->addItem("Five", 5);
	selector->addItem("Six", 6);
	selector->addItem("Seven", 7);
	selector->addItem("Height", 8);
	return selector;
}

Dice::Die
DiceWidget::getDie() const {
	Dice::Die die;
	for (int i = 0; i < _dieSideNumber->value(); ++i) {
		die.push_back(Dice::Face::create(_dieSides[i]->currentData().toInt()));
	}
	return die;
}

Dice::FaceTuple
DiceWidget::getTuple() const {
	Dice::FaceTuple tuple;
	for (int i = 0; i < _tupleSize->value(); ++i) {
		tuple.insert(Dice::Face::create(_tupleSides[i]->currentData().toInt()));
	}
	return tuple;
}
