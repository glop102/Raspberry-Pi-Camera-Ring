#3D Model Capture Rig

This project is an attempt to make a simple suite that makes having a raspberry pi based Capture Rig simple. The point is to have a number of pi's, each with a camera and mounted on a pole, capable of taking a picture simultaniously and then relay the images to a central admin station.

[Setup Guide](https://github.com/glop102/Raspberry-Pi-Camera-Ring/wiki/Setup-Guide)

##Concept

There are 3 computers in the system; Admin, Camera, Projector. The Admin controls the flow of the system and is the relay point of the images that just got captured. The Camera systems wait to be told to take a picture, and then upload the images to the admin after they have done so. The Projector systems display an image on a projector overhead to add noise to the subject so that the rendering program has more useful data to reconstruct with. There is the 4th computer, the client, which simply contacts the admin via a web-browser to give commands and to download a zipfile of the images take.

##Curent Phase

The current phase of the project is that of rapid prototyping. The feature set is currently planned, and some have stop-gap measures that do work but are not as nice as what is planned. Eventually this project will stabilize in terms of the core features and then simply will have features added on. The framework of adding new parts if rather simple, only requiring a new if-else pair to branch off into new directions. The current core feature set is mostly stable although using the stop-gap methods. Future updates should not change these, but simply improve the speed at which they operate up to the point of being capable of nearly instantaeous capture of a frame from all camera.

See the [wiki](https://github.com/glop102/Raspberry-Pi-Camera-Ring/wiki/todo) for a (really) rough list of work that is being done.