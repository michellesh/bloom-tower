import * as d3 from 'd3';

import { WIDTH, HEIGHT } from 'const';
import { degrees, distance, pointOnLine } from 'utils';
import { LED } from 'models/LED';

const center = { x: WIDTH / 2, y: HEIGHT / 2 };

const NUM_LEVELS = 7;
const LEVEL_EDGE_LEN_FT = [1, 2, 3, 4, 6, 8, 10];
const METERS_PER_FOOT = 0.3048;
const LEDS_PER_METER = 144;
//const NUM_LEDS_PER_EDGE = [44, 97, 136, 175, 263, 351, 432];
const NUM_LEDS_PER_EDGE = [10, 20, 30, 40, 60, 80, 100];
const MAX_EDGE_LEN_PX = 500; //355;

const ftToPx = d3
  .scaleLinear()
  .domain([0, d3.max(LEVEL_EDGE_LEN_FT)])
  .range([0, MAX_EDGE_LEN_PX]);

const Level = levelIndex => {
  const edgeLength = ftToPx(LEVEL_EDGE_LEN_FT[levelIndex]);
  const corners = {
    tl: { x: center.x - edgeLength / 2, y: center.y - edgeLength / 2 },
    tr: { x: center.x + edgeLength / 2, y: center.y - edgeLength / 2 },
    bl: { x: center.x - edgeLength / 2, y: center.y + edgeLength / 2 },
    br: { x: center.x + edgeLength / 2, y: center.y + edgeLength / 2 }
  };

  const topLeds = d3
    .range(0, 1, 1 / NUM_LEDS_PER_EDGE[levelIndex])
    .map(howFar =>
      LED(pointOnLine(corners.tl, corners.tr, howFar)).color('purple')
    );
  const rightLeds = d3
    .range(0, 1, 1 / NUM_LEDS_PER_EDGE[levelIndex])
    .map(howFar =>
      LED(pointOnLine(corners.tr, corners.br, howFar)).color('blue')
    );
  const bottomLeds = d3
    .range(0, 1, 1 / NUM_LEDS_PER_EDGE[levelIndex])
    .map(howFar =>
      LED(pointOnLine(corners.br, corners.bl, howFar)).color('green')
    );
  const leftLeds = d3
    .range(0, 1, 1 / NUM_LEDS_PER_EDGE[levelIndex])
    .map(howFar =>
      LED(pointOnLine(corners.bl, corners.tl, howFar)).color('yellow')
    );

  const topCenter = { x: corners.tl.x + edgeLength / 2, y: corners.tl.y };
  const rightCenter = { x: corners.tr.x, y: corners.tr.y + edgeLength / 2 };
  const bottomCenter = { x: corners.br.x - edgeLength / 2, y: corners.br.y };
  const leftCenter = { x: corners.bl.x, y: corners.bl.y - edgeLength / 2 };

  const topAngles = topLeds.map(led =>
    led.x < topCenter.x
      ? 360 -
        Math.round(
          degrees(
            Math.acos(distance(center, topCenter) / distance(led, center))
          )
        )
      : Math.round(
          degrees(
            Math.acos(distance(center, topCenter) / distance(led, center))
          )
        )
  );
  const rightAngles = rightLeds.map(led =>
    led.y < rightCenter.y
      ? 90 -
        Math.round(
          degrees(
            Math.acos(distance(center, rightCenter) / distance(led, center))
          )
        )
      : 90 +
        Math.round(
          degrees(
            Math.acos(distance(center, rightCenter) / distance(led, center))
          )
        )
  );
  const bottomAngles = bottomLeds.map(led =>
    led.x > bottomCenter.x
      ? 180 -
        Math.round(
          degrees(
            Math.acos(distance(center, bottomCenter) / distance(led, center))
          )
        )
      : 180 +
        Math.round(
          degrees(
            Math.acos(distance(center, bottomCenter) / distance(led, center))
          )
        )
  );
  const leftAngles = leftLeds.map(led =>
    led.y > leftCenter.y
      ? 270 -
        Math.round(
          degrees(
            Math.acos(distance(center, leftCenter) / distance(led, center))
          )
        )
      : 270 +
        Math.round(
          degrees(
            Math.acos(distance(center, leftCenter) / distance(led, center))
          )
        )
  );

  const allLeds = [topLeds, rightLeds, bottomLeds, leftLeds].flatMap(x => x);
  const angles = [topAngles, rightAngles, bottomAngles, leftAngles].flatMap(
    x => x
  );

  return {
    allLeds,
    angles,
    radii: allLeds.map(led => Math.round(distance(led, center))),
    draw: context => {
      context.rect(corners.tl.x, corners.tl.y, edgeLength, edgeLength);
      context.lineWidth = 1;
      context.strokeStyle = 'white';
      context.stroke();
    }
  };
};

export const LEVELS = d3.range(NUM_LEVELS).map(Level);
