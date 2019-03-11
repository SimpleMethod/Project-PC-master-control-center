#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "FrontEnd.h"
#include "librarycollection.h"

/**
 * @class Main
 *
 * @brief Jest to podstawowy plik zajmująca się obsługą aplikacji. Znajdują się w niej wywołanie głównych metody pozostałych klas.
 *
 * @note Plik zajmujący się inicjacją aplikacji.
 * Jest to podstawowy plik zajmująca się obsługą aplikacji. Znajdują się w niej wywołanie głównych metody pozostałych klas.
 *
 */

/// Jest to podstawowy plik zajmująca się obsługą aplikacji. Znajdują się w niej wywołanie głównych metody pozostałych klas.
using namespace BackEndSpace;
using namespace FrontEndSpace;

int main(int argc, char* argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    /// Wywołanie Front endu.
    FrontEnd back;
    /// Dzięki QMLContext mamy możliwość podpięcia się pod JavaScript.
    QQmlContext* ctx = engine.rootContext();
    /// Podpięcie klasy FrontEnd pod JavaScript
    ctx->setContextProperty("back", &back);
     /// Uruchomienie prasowania i ładowania JavaScript
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));
    ///Sprawdzanie, czy Steam jest uruchomiony
    if (SteamAPI_RestartAppIfNecessary(674600)) {
        return app.exec();
    }
    ///Sprawdzanie, czy API Steam zostało jest poprawnie inicjalizowane
    if (!SteamAPI_Init()) {
        return app.exec();
    } else {
        /// Inicjalizacja stron JavaScript
        back.initialization_QML_MAIN();
        back.initialization_QML_RIGHTBAR();
        back.initialization_QML_LED();
        back.initialization_QML_OLED();
    }

    return app.exec();
}
