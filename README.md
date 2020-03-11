# bear_with_me

Bear With Me is the beginnings of a survival game I worked on. The game is built with SFML.

In the game, the player can walk around a randomly generated forest and has a meter that fills up with time allowing them to press space bar and being sprinting.

Some notable pieces of code.

The draw and collision system uses the player position and only draws and checks collision with nearby objects. This allows the creation of large worlds with no added lag.

The world creation is set up to create any size rectangle and randomly create and space out trees within the border. This is done by splitting the large rectangle up into smaller ones that are than treated individually.

The meter that tracks the players stamina was programmed from just lines and dots and can be put into any pattern depending on how many slots the player has for stamina.
For example, if the player only had 5 available slots the meter would appear as a pentagon, if 8 it can change to an octagon.

The game clock and time management is important for both the players meter fill up time and for the duration of the players sprint and how that drains the meter.

The collisions with trees are "soft". Meaning the player can slowly push through them. In sprint mode, the player can barrel through trees.

The last feature implemented was animation. Sprite sheets are a foreign concept to me and I attempt to programmatically animate the bear by having a paw that would swing in front of the player when the player clicks. This does not look nearly as natural as sprit sheets but since I am not very artistically inclined, this is where I stopped working on the project.
