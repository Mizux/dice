/* @file
 */

#include "DiceWidget.hpp"
#include <QApplication>

int
main(int argc, char** argv) {
	QApplication app(argc, argv);
	app.setOrganizationName("Mizux");
	app.setApplicationName("Dice");

	DiceWidget main;
	main.show();

	return app.exec();
}
