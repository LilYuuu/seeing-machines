# Assignment 2: Video Effect
### Update on Oct 4, 2023
By using the `crop` function, I was able to apply the blur effect only to the face tracker.

![ezgif com-video-to-gif](https://github.com/LilYuuu/seeing-machines/assets/44248733/d588fcde-735f-4b60-a6f4-13fe93f329e9)

---

### Oct 3, 2023

![Screenshot 2023-10-03 at 10 39 03 AM](https://github.com/LilYuuu/seeing-machines/assets/44248733/1a810f98-4377-4e9e-8029-c3b2781d0661)

For this assignment, I wanted to create a filter utilizing ofxCv to track faces and apply a blur effect to the tracked region.

However, I ran into an error when trying to create an `ofImage` from the tracked region. For now, I am applying the blur effect to the whole video capture. The blurred area moves along with the face tracker.

I also implemented a GUI control to freeze/restart the video capture.
