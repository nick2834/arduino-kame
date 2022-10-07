from kivymd.app import MDApp
from kivy.utils import platform
from kivy.core.window import Window
from kivy.lang.builder import Builder
from views.home_page import HomePage
if platform != "android":
    Window.size = (350, 650)
# icon   https://materialdesignicons.com/


class ArduinoRobotApp(MDApp):
    def build(self):
        self.load_all_kv_files()
        return HomePage()

    def load_all_kv_files(self):
        Builder.load_file('views/home_page.kv')
        Builder.load_file('components/appbar.kv')
        # Builder.load_file('libs/components/story_creator.kv')
        Builder.load_file('components/bottom_nav.kv')
        # Builder.load_file('libs/components/circular_avatar_image.kv')
        # Builder.load_file('libs/components/post_card.kv')

    def on_start(self):
        self.root.dispatch('on_enter')


if __name__ == "__main__":
    ArduinoRobotApp().run()
