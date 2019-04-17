import pygame
from network import Network

class Game:

    def __init__(self, w, h):
        self.network = Network()
        self.width = w
        self.height = h
        self.canvas = Canvas(self.width, self.height, "Title")

    def run(self):
        clock = pygame.time.Clock()
        run = True
        while run:
            clock.tick(60)

            self.canvas.draw_background()
            self.canvas.update()

        pygame.quit()

    def send_data(self):
        data = self.net.send(data)
        return data


class Canvas:

    def __init__(self, w, h, name="None"):
        self.width = w
        self.height = h
        self.screen = pygame.display.set_mode((w,h))
        pygame.display.set_caption(name)

    @staticmethod
    def update():
        pygame.display.update()

    def get_canvas(self):
        return self.screen

    def draw_background(self):
        self.screen.fill((255,255,255))
