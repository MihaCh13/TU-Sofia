export type EventType = 'lecture' | 'seminar' | 'lab' | 'makeup';
export type WeekType = 'all' | 'odd' | 'even';

export interface ScheduleEvent {
  id: string;
  title: string;
  professor: string;
  room: string;
  day: string;
  startTime: string;
  endTime: string;
  type: EventType;
  weekType: WeekType;
  credits?: number;
  notes?: string;
}

export const DAYS = ['Понеделник', 'Вторник', 'Сряда', 'Четвъртък', 'Петък'] as const;

export const TIME_SLOTS = [
  '07:30', '08:00', '08:30', '09:00', '09:30', '10:00', '10:30', '11:00', 
  '11:30', '12:00', '12:30', '13:00', '13:30', '14:00', '14:30', '15:00',
  '15:30', '16:00', '16:30', '17:00', '17:30', '18:00', '18:30', '19:00'
] as const;

export const EVENT_TYPES: Record<EventType, { label: string; className: string }> = {
  lecture: { label: 'Лекция', className: 'lecture-bg' },
  seminar: { label: 'Семинар', className: 'seminar-bg' },
  lab: { label: 'Лабораторни', className: 'lab-bg' },
  makeup: { label: 'Поправка', className: 'makeup-bg' },
};

export const WEEK_TYPES: Record<WeekType, string> = {
  all: 'Всяка седмица',
  odd: 'Нечетна седмица',
  even: 'Четна седмица',
};
