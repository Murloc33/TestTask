#include "settings.h"

#include <QStandardPaths>

QSettings *Settings::settings()
{
	static QScopedPointer<QSettings> m_settings;

	if (m_settings.isNull()) {
		QString ini = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation)
					  + "/TestTask.ini";
		m_settings.reset(new QSettings(ini, QSettings::IniFormat));
	}
	return m_settings.data();
}
