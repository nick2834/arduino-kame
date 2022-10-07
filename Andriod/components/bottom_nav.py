from kivymd.uix.boxlayout import MDBoxLayout
from kivy.properties import StringProperty


class BottomNav(MDBoxLayout):
    badge_icon = StringProperty("")

    def on_tab_press(self, args):
        print(args.name)
        self.badge_icon = "numeric-2"
