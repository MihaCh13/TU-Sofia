export interface ScheduleEvent {
  id: string;
  title: string;
  professor: string;
  room: string;
  day: string;
  start_time: string;
  end_time: string;
  color: string;
  credits?: number;
}

export interface CalendarConfig {
  winterSemester: { start: string; end: string };
  summerSemester: { start: string; end: string };
  winterRegularSession: { start: string; end: string };
  winterRetakeSession: { start: string; end: string };
  summerRegularSession: { start: string; end: string };
  annualRetakeSession: { start: string; end: string };
  liquidationSession: { start: string; end: string };
}

export const DAYS = ['Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday'];

export const DAY_NAMES: Record<string, string> = {
  Monday: 'Понеделник',
  Tuesday: 'Вторник',
  Wednesday: 'Сряда',
  Thursday: 'Четвъртък',
  Friday: 'Петък',
};

export const TIME_SLOTS = [
  { start: '08:00', end: '09:00', lunch: false },
  { start: '09:00', end: '10:00', lunch: false },
  { start: '10:00', end: '11:00', lunch: false },
  { start: '11:00', end: '12:00', lunch: false },
  { start: '12:00', end: '13:00', lunch: true },
  { start: '13:00', end: '14:00', lunch: false },
  { start: '14:00', end: '15:00', lunch: false },
  { start: '15:00', end: '16:00', lunch: false },
  { start: '16:00', end: '17:00', lunch: false },
  { start: '17:00', end: '18:00', lunch: false },
];

export const COLOR_OPTIONS = [
  '#ff6b6b',
  '#4ecdc4',
  '#45b7d1',
  '#ffa502',
  '#f368e0',
  '#90ee90',
  '#87ceeb',
  '#dda0dd',
];

export function getSlotIndex(time: string): number {
  return TIME_SLOTS.findIndex((slot) => slot.start === time);
}

export function getSlotCountBetween(startTime: string, endTime: string): number {
  const startIdx = getSlotIndex(startTime);
  const endIdx = getSlotIndex(endTime);
  
  if (startIdx === -1 || endIdx === -1) return 1;
  
  let count = 0;
  for (let i = startIdx; i < endIdx; i++) {
    if (!TIME_SLOTS[i].lunch) {
      count++;
    }
  }
  return Math.max(1, count);
}

export function formatTime(time: string): string {
  return time;
}
