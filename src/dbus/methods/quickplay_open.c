/**
 * WarfaceBot, a blind XMPP client for Warface (FPS)
 * Copyright (C) 2015-2017 Levak Borok <levak92@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <gio/gio.h>

#include <wb_dbus_methods.h>

#include <wb_cmd.h>

struct cb_args
{
    Warfacebot *object;
    GDBusMethodInvocation *invocation;
};

// TODO Result?
static void quickplay_cb(void *args)
{
    struct cb_args *a = (struct cb_args *) args;

    warfacebot_complete_quickplay_open(a->object, a->invocation);

    g_free(a);
}

/*
** DBus method call: "QuickplayOpen"
*/
gboolean on_handle_quickplay_open(Warfacebot *object,
                                  GDBusMethodInvocation *invocation,
                                  const gchar *arg_MapName)
{
    struct cb_args *a = g_new0(struct cb_args, 1);

    a->object = object;
    a->invocation = invocation;

    cmd_quickplay("open", arg_MapName, quickplay_cb, a);

    return TRUE;
}
