#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <controllers/master-controller.h>
#include <controllers/command-controller.h>
#include <controllers/navigation-controller.h>
#include <data/datetime-decorator.h>
#include <data/enumerator-decorator.h>
#include <data/int-decorator.h>
#include <data/string-decorator.h>
#include <data/dropdown.h>
#include <data/dropdownvalue.h>
#include <framework/command.h>
#include <models/clientsearch.h>
#include <models/address.h>
#include <models/appointment.h>
#include <models/client.h>
#include <models/contact.h>

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

	QGuiApplication app(argc, argv);

    /***
     * Register the classes type with QML engine
     * adding the types metadata to a module CM, version number 1.0
     * then give a reference to this type i.e MasterController in QML markup
     */

	qmlRegisterType<cm::controllers::MasterController>("CM", 1, 0, "MasterController");
	qmlRegisterType<cm::controllers::NavigationController>("CM", 1, 0, "NavigationController");
	qmlRegisterType<cm::controllers::CommandController>("CM", 1, 0, "CommandController");

	qmlRegisterType<cm::data::DateTimeDecorator>("CM", 1, 0, "DateTimeDecorator");
	qmlRegisterType<cm::data::EnumeratorDecorator>("CM", 1, 0, "EnumeratorDecorator");
	qmlRegisterType<cm::data::IntDecorator>("CM", 1, 0, "IntDecorator");
	qmlRegisterType<cm::data::StringDecorator>("CM", 1, 0, "StringDecorator");

    qmlRegisterType<cm::models::ClientSearch>("CM", 1, 0, "ClientSearch");
	qmlRegisterType<cm::models::Address>("CM", 1, 0, "Address");
	qmlRegisterType<cm::models::Appointment>("CM", 1, 0, "Appointment");
	qmlRegisterType<cm::models::Client>("CM", 1, 0, "Client");
	qmlRegisterType<cm::models::Contact>("CM", 1, 0, "Contact");

	qmlRegisterType<cm::framework::Command>("CM", 1, 0, "Command");

    qmlRegisterType<cm::data::DropDownValue>("CM",1 , 0, "DropDownValue");
    qmlRegisterType<cm::data::DropDown>("CM", 1, 0, "DropDown");

    // we instantiate the instance of MasterController and inject it into the root QML context

	cm::controllers::MasterController masterController;

	QQmlApplicationEngine engine;
	engine.addImportPath("qrc:/");
	engine.rootContext()->setContextProperty("masterController", &masterController);
	engine.load(QUrl(QStringLiteral("qrc:/views/MasterView.qml")));

	if (engine.rootObjects().isEmpty())
		return -1;

	return app.exec();
}
