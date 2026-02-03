'use client';

import { useScheduleStore } from '@/lib/schedule-store';
import { DAYS, TIME_SLOTS, EVENT_TYPES, WEEK_TYPES } from '@/lib/schedule-types';
import type { ScheduleEvent } from '@/lib/schedule-types';
import { cn } from '@/lib/utils';
import { Clock, MapPin, User } from 'lucide-react';

interface ScheduleTableProps {
  onCellClick: (day: string, startTime: string) => void;
  onEventClick: (event: ScheduleEvent) => void;
}

export function ScheduleTable({ onCellClick, onEventClick }: ScheduleTableProps) {
  const events = useScheduleStore((state) => state.events);

  const getEventsForSlot = (day: string, time: string) => {
    return events.filter(
      (event) => event.day === day && event.startTime === time
    );
  };

  const isSlotOccupied = (day: string, time: string) => {
    return events.some((event) => {
      const startIndex = TIME_SLOTS.indexOf(event.startTime as typeof TIME_SLOTS[number]);
      const endIndex = TIME_SLOTS.indexOf(event.endTime as typeof TIME_SLOTS[number]);
      const currentIndex = TIME_SLOTS.indexOf(time as typeof TIME_SLOTS[number]);
      return event.day === day && currentIndex >= startIndex && currentIndex < endIndex;
    });
  };

  const getEventDuration = (event: ScheduleEvent) => {
    const startIndex = TIME_SLOTS.indexOf(event.startTime as typeof TIME_SLOTS[number]);
    const endIndex = TIME_SLOTS.indexOf(event.endTime as typeof TIME_SLOTS[number]);
    return endIndex - startIndex;
  };

  const displayTimes = TIME_SLOTS.filter((_, i) => i % 2 === 0);

  return (
    <div className="flex-1 overflow-auto p-4">
      <div className="min-w-[900px]">
        <div className="grid grid-cols-6 gap-1">
          {/* Header row */}
          <div className="p-3 text-center font-medium text-muted-foreground bg-muted/50 rounded-lg">
            <Clock className="w-4 h-4 mx-auto mb-1" />
            Час
          </div>
          {DAYS.map((day) => (
            <div
              key={day}
              className="p-3 text-center font-semibold bg-muted/50 rounded-lg text-foreground"
            >
              {day}
            </div>
          ))}

          {/* Time slots */}
          {displayTimes.map((time) => (
            <>
              <div
                key={`time-${time}`}
                className="p-3 text-center text-sm font-medium text-muted-foreground bg-muted/30 rounded-lg flex items-center justify-center"
              >
                {time}
              </div>
              {DAYS.map((day) => {
                const slotEvents = getEventsForSlot(day, time);
                const isOccupied = isSlotOccupied(day, time) && slotEvents.length === 0;

                if (isOccupied) {
                  return <div key={`${day}-${time}`} className="min-h-[80px]" />;
                }

                if (slotEvents.length > 0) {
                  return (
                    <div key={`${day}-${time}`} className="relative">
                      {slotEvents.map((event) => {
                        const duration = getEventDuration(event);
                        const typeConfig = EVENT_TYPES[event.type];
                        return (
                          <div
                            key={event.id}
                            onClick={() => onEventClick(event)}
                            className={cn(
                              'absolute inset-x-0 top-0 p-2 rounded-lg cursor-pointer transition-all hover:shadow-lg hover:scale-[1.02] overflow-hidden',
                              typeConfig.className
                            )}
                            style={{ height: `${duration * 84}px` }}
                          >
                            <div className="flex flex-col h-full">
                              <div className="flex items-start justify-between gap-1 mb-1">
                                <h4 className="font-semibold text-sm text-slate-800 line-clamp-2 leading-tight">
                                  {event.title}
                                </h4>
                                {event.weekType !== 'all' && (
                                  <span className="text-[10px] px-1.5 py-0.5 rounded bg-white/70 text-slate-600 whitespace-nowrap">
                                    {event.weekType === 'odd' ? 'Нч' : 'Ч'}
                                  </span>
                                )}
                              </div>
                              <div className="text-xs text-slate-600 space-y-0.5 mt-auto">
                                <div className="flex items-center gap-1">
                                  <User className="w-3 h-3" />
                                  <span className="truncate">{event.professor}</span>
                                </div>
                                <div className="flex items-center gap-1">
                                  <MapPin className="w-3 h-3" />
                                  <span>Зала {event.room}</span>
                                </div>
                              </div>
                              <div className="mt-1">
                                <span className="text-[10px] px-1.5 py-0.5 rounded bg-white/50 text-slate-600">
                                  {typeConfig.label}
                                </span>
                              </div>
                            </div>
                          </div>
                        );
                      })}
                    </div>
                  );
                }

                return (
                  <div
                    key={`${day}-${time}`}
                    onClick={() => onCellClick(day, time)}
                    className="min-h-[80px] rounded-lg border border-dashed border-border/50 hover:bg-muted/30 hover:border-primary/30 cursor-pointer transition-all"
                  />
                );
              })}
            </>
          ))}
        </div>
      </div>
    </div>
  );
}
