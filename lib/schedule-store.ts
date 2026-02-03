import { create } from 'zustand';
import { persist } from 'zustand/middleware';
import type { ScheduleEvent, CalendarConfig } from './schedule-types';

interface ScheduleState {
  events: ScheduleEvent[];
  calendarConfig: CalendarConfig | null;
  semester: 'winter' | 'summer';
  vacations: string[];
  
  addEvent: (event: ScheduleEvent) => void;
  updateEvent: (id: string, event: Partial<ScheduleEvent>) => void;
  deleteEvent: (id: string) => void;
  setCalendarConfig: (config: CalendarConfig) => void;
  setSemester: (semester: 'winter' | 'summer') => void;
  setVacations: (vacations: string[]) => void;
  addVacation: (date: string) => void;
  removeVacation: (date: string) => void;
}

export const useScheduleStore = create<ScheduleState>()(
  persist(
    (set) => ({
      events: [],
      calendarConfig: null,
      semester: 'winter',
      vacations: [],

      addEvent: (event: ScheduleEvent) =>
        set((state) => ({
          events: [...state.events, event],
        })),

      updateEvent: (id: string, updates: Partial<ScheduleEvent>) =>
        set((state) => ({
          events: state.events.map((event) =>
            event.id === id ? { ...event, ...updates } : event
          ),
        })),

      deleteEvent: (id: string) =>
        set((state) => ({
          events: state.events.filter((event) => event.id !== id),
        })),

      setCalendarConfig: (config: CalendarConfig) =>
        set({ calendarConfig: config }),

      setSemester: (semester: 'winter' | 'summer') =>
        set({ semester }),

      setVacations: (vacations: string[]) =>
        set({ vacations }),

      addVacation: (date: string) =>
        set((state) => ({
          vacations: [...state.vacations, date],
        })),

      removeVacation: (date: string) =>
        set((state) => ({
          vacations: state.vacations.filter((v) => v !== date),
        })),
    }),
    {
      name: 'schedule-storage',
      skipHydration: true,
    }
  )
);
