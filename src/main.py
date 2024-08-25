import pygame

def main():
    pygame.init()

    window = pygame.display.set_mode((400, 300))
    pygame.display.set_caption('runvis')

    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        window.fill((0,0,0))
        pygame.draw.circle(window, (255, 0, 0), (200, 150), 50)
        pygame.display.flip()

    pygame.quit()


main();
