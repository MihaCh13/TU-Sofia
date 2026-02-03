import { create } from 'zustand';
import { persist } from 'zustand/middleware';
import type { ScheduleEvent } from './schedule-types';

interface ScheduleState {
  events: ScheduleEvent[];
  addEvent: (event: ScheduleEvent) => void;
  updateEvent: (id: string, event: Partial<ScheduleEvent>) => void;
  deleteEvent: (id: string) => void;
  semesterStart: string;
  semesterEnd: string;
  setSemesterDates: (start: string, end: string) => void;
}

const initialEvents: ScheduleEvent[] = [
  {
    id: '1',
    title: 'Математика 1',
    professor: 'доц. д-р Иванов',
    room: '2234',
    day: 'Понеделник',
    startTime: '08:00',
    endTime: '10:00',
    type: 'lecture',
    weekType: 'all',
    credits: 6,
  },
  {
    id: '2',
    title: 'Програмиране',
    professor: 'проф. Петров',
    room: '1320',
    day: 'Понеделник',
    startTime: '10:00',
    endTime: '12:00',
    type: 'lab',
    weekType: 'odd',
    credits: 5,
  },
  {
    id: '3',
    title: 'Физика',
    professor: 'доц. Георгиев',
    room: '3415',
    day: 'Вторник',
    startTime: '08:00',
    endTime: '10:00',
    type: 'lecture',
    weekType: 'all',
    credits: 5,
  },
  {
    id: '4',
    title: 'Английски език',
    professor: 'ст. пр. Димитрова',
    room: '4102',
    day: 'Вторник',
    startTime: '14:00',
    endTime: '16:00',
    type: 'seminar',
    weekType: 'all',
    credits: 3,
  },
  {
    id: '5',
    title: 'Основи на електротехниката',
    professor: 'проф. Стоянов',
    room: '2118',
    day: 'Сряда',
    startTime: '09:00',
    endTime: '11:00',
    type: 'lecture',
    weekType: 'all',
    credits: 6,
  },
  {
    id: '6',
    title: 'Програмиране - упражнения',
    professor: 'ас. Николов',
    room: '1320',
    day: 'Четвъртък',
    startTime: '10:00',
    endTime: '12:00',
    type: 'lab',
    weekType: 'even',
    credits: 5,
  },
  {
    id: '7',
    title: 'Дискретни структури',
    professor: 'доц. Маринов',
    room: '2234',
    day: 'Петък',
    startTime: '08:00',
    endTime: '10:00',
    type: 'lecture',
    weekType: 'all',
    credits: 4,
  },
];

export const useScheduleStore = create<ScheduleState>()(
  persist(
    (set) => ({
      events: initialEvents,
      addEvent: (event) =>
        set((state) => ({ events: [...state.events, event] })),
      updateEvent: (id, updatedEvent) =>
        set((state) => ({
          events: state.events.map((e) =>
            e.id === id ? { ...e, ...updatedEvent } : e
          ),
        })),
      deleteEvent: (id) =>
        set((state) => ({
          events: state.events.filter((e) => e.id !== id),
        })),
      semesterStart: '2024-09-16',
      semesterEnd: '2025-01-17',
      setSemesterDates: (start, end) =>
        set({ semesterStart: start, semesterEnd: end }),
    }),
    {
      name: 'schedule-storage',
      skipHydration: true,
    }
  )
);
