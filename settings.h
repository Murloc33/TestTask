#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

class Settings
{
	Settings() = delete;

public:
	static QSettings* settings();

};

#endif // SETTINGS_H
