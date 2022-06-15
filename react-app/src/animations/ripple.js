import { clearCanvas } from 'utils';
import { showLEDs } from 'animations';

export const ripple = (context, levels) => {
  clearCanvas(context);

  let radius = 0;
  const threshold = 10;

  const _ripple = () => {
    levels.forEach((level, d) => {
      level.allLeds = level.allLeds.map((led, i) =>
        Math.abs(level.radii[i] - radius) < threshold ? led.on() : led.off()
      );
    });

    showLEDs(context, levels);
    radius++;
    if (radius >= 500) {
      radius = 0;
    }
    window.reqId = window.requestAnimationFrame(_ripple);
  };

  window.reqId = window.requestAnimationFrame(_ripple);
};
