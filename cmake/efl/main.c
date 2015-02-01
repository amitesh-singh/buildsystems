#include <Elementary.h>

int main(int argc, char **argv)
{
   elm_init(argc, argv);

   Evas_Object *win = elm_win_util_standard_add("cmakeexample",
                                                "cmake");
   elm_win_autodel_set(win, 1);
   evas_object_resize(win, 200, 200);
   evas_object_show(win);

   elm_run();
   elm_shutdown();

   return 0;
}
