import { clearCanvas } from 'utils';

export const showLEDs = (context, levels) => {
  clearCanvas(context);
  levels.forEach(level => {
    level.draw(context);
    level.allLeds.forEach(led => led.draw(context));
  });
};

export * from './ripple';
