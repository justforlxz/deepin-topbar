#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QtCore>

namespace Dock {

#define DOCK_PLUGIN_MIME    "dock/plugin"

#define PROP_DISPLAY_MODE   "DisplayMode"
///
/// \brief The DisplayMode enum
/// spec dock display mode
///
enum DisplayMode
{
    Fashion     = 0,
    Efficient   = 1,
    // deprecreated
//    Classic     = 2,
};

#define PROP_HIDE_MODE      "HideMode"
///
/// \brief The HideMode enum
/// spec dock hide behavior
///
enum HideMode
{
    KeepShowing     = 0,
    KeepHidden      = 1,
    SmartHide       = 3,
};

#define PROP_POSITION       "Position"
///
/// \brief The Position enum
/// spec dock position, dock always placed at primary screen,
/// so all position is the primary screen edge.
///
enum Position
{
    Top         = 0,
    Right       = 1,
    Bottom      = 2,
    Left        = 3,
};

#define PROP_HIDE_STATE     "HideState"
///
/// \brief The HideState enum
/// spec current dock should hide or shown.
/// this argument works only HideMode is SmartHide
///
enum HideState
{
    Unknown     = 0,
    Show        = 1,
    Hide        = 2,
};

}

Q_DECLARE_METATYPE(Dock::DisplayMode)
Q_DECLARE_METATYPE(Dock::Position)

#endif // CONSTANTS_H
