'use client';

import { create } from 'zustand';
import { persist } from 'zustand/middleware';
import type { ScheduleEvent } from './schedule-types';
import { generateId } from './schedule-types';

export interface CalendarConfig {
  winterSemester: { start: string; end: string };
  winterRegularSession: { start: string; end: string };
  winterRetakeSession: { start: string; end: string };
  summerSemester: { start: string; end: string };
  summerRegularSession: { start: string; end: string };
  annualRetakeSession: { start: string; end: string };
  liquidationSession: { start: string; end: string };
}

interface ScheduleStore {
  events: ScheduleEvent[];
  addEvent: (event: Omit<ScheduleEvent, 'id'>) => void;
  updateEvent: (id: string, event: Partial<ScheduleEvent>) => void;
  deleteEvent: (id: string) => void;
  semester: 'winter' | 'summer';
  setSemester: (semester: 'winter' | 'summer') => void;
  calendarConfig: CalendarConfig | null;
  academicYear: string;
  setAcademicYear: (year: string) => void;
  setCalendarConfig: (config: CalendarConfig) => void;
  clearCalendarConfig: () => void;
  holidays: string[];
  addHoliday: (date: string) => void;
  removeHoliday: (date: string) => void;
  vacations: string[];
  addVacation: (date: string) => void;
  removeVacation: (date: string) => void;
}

export const useScheduleStore = create<ScheduleStore>()(
  persist(
    (set) => ({
      events: [],
      addEvent: (event) =>
        set((state) => ({
          events: [...state.events, { ...event, id: generateId() }],
        })),
      updateEvent: (id, updatedEvent) =>
        set((state) => ({
          events: state.events.map((evt) =>
            evt.id === id ? { ...evt, ...updatedEvent } : evt
          ),
        })),
      deleteEvent: (id) =>
        set((state) => ({
          events: state.events.filter((evt) => evt.id !== id),
        })),
      semester: 'winter',
      setSemester: (semester) => set({ semester }),
      academicYear: '2025/2026',
      setAcademicYear: (year) => set({ academicYear: year }),
      vacations: ['2025-12-22', '2025-12-23', '2025-12-24', '2025-12-25', '2025-12-26', '2025-12-27', '2025-12-28', '2025-12-29', '2025-12-30', '2025-12-31', '2026-01-01', '2026-01-02', '2026-01-03', '2026-01-04'],
      calendarConfig: {
        winterSemester: { start: '2025-09-23', end: '2025-12-20' },
        winterRegularSession: { start: '2026-01-05', end: '2026-01-24' },
        winterRetakeSession: { start: '2026-01-26', end: '2026-02-07' },
        summerSemester: { start: '2026-02-09', end: '2026-05-09' },
        summerRegularSession: { start: '2026-05-11', end: '2026-05-30' },
        annualRetakeSession: { start: '2026-06-01', end: '2026-06-20' },
        liquidationSession: { start: '2025-09-15', end: '2025-09-20' },
      },
      setCalendarConfig: (config) => set({ calendarConfig: config }),
      clearCalendarConfig: () => set({ calendarConfig: null }),
      holidays: [],
      addHoliday: (date) => set((state) => ({ 
        holidays: state.holidays.includes(date) ? state.holidays : [...state.holidays, date] 
      })),
      removeHoliday: (date) => set((state) => ({ 
        holidays: state.holidays.filter(d => d !== date) 
      })),
      vacations: [],
      addVacation: (date) => set((state) => ({ 
        vacations: state.vacations.includes(date) ? state.vacations : [...state.vacations, date] 
      })),
      removeVacation: (date) => set((state) => ({ 
        vacations: state.vacations.filter(d => d !== date) 
      })),
    }),
    {
      name: 'schedule-storage',
      version: 2,
    }
  )
);
