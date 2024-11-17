""" Module providing abstract menu """

import abc
import sys
import typing
import pygame

class SelectionMenu(abc.ABC): #pylint: disable=too-many-instance-attributes
    """ Class representing game menu. """

    def __init__(self, screen_size: typing.Tuple[int, int], #pylint: disable=too-many-arguments
                    options: typing.List[str], title: str,
                    background_color: typing.Optional[typing.Tuple[int, int, int]] = (30, 30, 30),
                    text_color: typing.Optional[typing.Tuple[int, int, int]] = (255, 255, 255),
                    selected_color: typing.Optional[typing.Tuple[int, int, int]] = (255, 255, 0),
                    defaut_font: typing.Optional[pygame.font.Font] = None,
                    title_font: typing.Optional[pygame.font.Font] = None
                ):

        pygame.init() # pylint: disable=no-member

        self.screen_size = screen_size # width, height
        self.options = options
        self.title = title
        self.background_color = background_color
        self.text_color = text_color
        self.selected_color = selected_color

        self.defaut_font = defaut_font if defaut_font else pygame.font.Font(None, 50)
        self.title_font = title_font if title_font else pygame.font.Font(None, 70)

        self.__screen = pygame.display.set_mode(self.screen_size)
        self.selected_option = 0
        self.main = self.running_option = self
        self.running = True

        pygame.display.set_caption("Game Menu")

    @abc.abstractmethod
    def select_option(self) -> None:
        """ Selects option in menu. """

    def draw_menu(self) -> None:
        """ Draw menu to be updated every frame. """

        margin = 0.1

        self.__screen.fill(self.background_color)

        rendered_title = self.title_font.render(self.title, True, self.text_color)
        title_x_coordinate = self.screen_size[0] // 2 - rendered_title.get_width() // 2
        title_y_coordinate = self.screen_size[1] * margin
        self.__screen.blit(rendered_title, (title_x_coordinate, title_y_coordinate))

        options_space = self.screen_size[1] - title_y_coordinate - self.screen_size[1]*margin
        space_between_options = options_space // len(self.options)

        for i, option in enumerate(self.options):
            color = self.selected_color if i == self.selected_option else self.text_color
            text = self.defaut_font.render(option, True, color)
            option_x_coordinate = self.screen_size[0] // 2 - text.get_width() // 2
            option_y_coordinate = title_y_coordinate + (i+1) * space_between_options \
                                    - text.get_height() // 2
            self.__screen.blit(text, (option_x_coordinate, option_y_coordinate))

    def process_events(self, events) -> int:
        """ Process events for running menu. """

        for event in events:
            if event.type == pygame.QUIT: # pylint: disable=no-member
                return -1

            if event.type == pygame.KEYDOWN: # pylint: disable=no-member

                if event.key == pygame.K_UP: # pylint: disable=no-member
                    self.selected_option -= 1
                    self.selected_option %= len(self.options)

                elif event.key == pygame.K_DOWN: # pylint: disable=no-member
                    self.selected_option += 1
                    self.selected_option %= len(self.options)

                elif event.key == pygame.K_RETURN: # pylint: disable=no-member
                    self.select_option()
                    return self.selected_option

        return None

    def show(self) -> None:
        """ Menu main loop. """
        while self.running:

            events = pygame.event.get()
            option = self.running_option.process_events(events)
            if option == -1:
                self.running = False

            self.running_option.draw_menu()
            pygame.display.flip() # update screen

        pygame.quit() # pylint: disable=no-member
        sys.exit()
