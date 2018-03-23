import turtle

window = turtle.Screen()
window.bgcolor("red")


def draw_square(some_turtle):
    for t in range(1, 5):
        some_turtle.forward(100)
        some_turtle.right(90)


def draw_circle(some_turtle):
    some_turtle.circle(100)


def draw_triangle(some_turtle):
    for t in range(1, 4):
        some_turtle.forward(100)
        some_turtle.right(120)


jack = turtle.Turtle()
jack.shape("turtle")
jack.color("blue")
jack.speed(2)

for i in range(1, 37):
    draw_square(jack)
    jack.right(10)
# draw_circle(jack)
# draw_triangle(jack)
window.exitonclick()
