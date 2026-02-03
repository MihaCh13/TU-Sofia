'use client';

import type { ScheduleEvent } from '@/lib/schedule-types';
import { EventBlock } from './event-block';
import { Plus } from 'lucide-react';
import { cn } from '@/lib/utils';

interface ScheduleCellProps {
  events: ScheduleEvent[];
  onCellClick: () => void;
  onEventClick: (event: ScheduleEvent) => void;
  rowSpan?: number;
  height?: number;
}

export function ScheduleCell({ 
  events, 
  onCellClick, 
  onEventClick,
  rowSpan = 1,
  height = 100
}: ScheduleCellProps) {
  // FIX #1: Do NOT filter out makeup events - treat them like regular events
  // Sort ALL events by week_cycle only
  const oddWeekEvents = events.filter(e => e.week_cycle === 'odd');
  const evenWeekEvents = events.filter(e => e.week_cycle === 'even');
  const everyWeekEvents = events.filter(e => e.week_cycle === 'every');

  const isEmpty = events.length === 0;
  const totalEvents = events.length;

  // Render empty cell
  if (isEmpty) {
    return (
      <td 
        className={cn("schedule-cell empty-cell border border-border")}
        style={{ height: `${height}px` }}
        rowSpan={rowSpan}
        onClick={onCellClick}
      >
        <div className="h-full flex items-center justify-center text-muted-foreground/40 text-sm font-medium cursor-pointer hover:text-muted-foreground/60 transition-colors">
          <Plus className="w-5 h-5" />
        </div>
      </td>
    );
  }

  // FIX #3: GRID 2x2 LAYOUT for 3+ events (collision case)
  if (totalEvents >= 3) {
    return (
      <td 
        className="schedule-cell border border-border p-1"
        style={{ height: `${height}px` }}
        rowSpan={rowSpan}
      >
        <div className="grid-2x2">
          {events.slice(0, 4).map((event) => (
            <div key={event.id} className="grid-2x2-item">
              <EventBlock 
                event={event} 
                isCompact
                onClick={() => onEventClick(event)} 
              />
            </div>
          ))}
        </div>
      </td>
    );
  }

  // Check for odd/even alternation
  const hasOdd = oddWeekEvents.length > 0;
  const hasEven = evenWeekEvents.length > 0;

  // Helper function to get background class based on subject type and event type
  const getTriangleBgClass = (event: ScheduleEvent | undefined) => {
    if (!event) return 'triangle-empty-bg';
    // Makeup events use makeup-bg, otherwise use subject type
    if (event.event_type === 'makeup') return 'triangle-makeup-bg';
    if (event.subject_type === 'lecture') return 'triangle-lecture-bg';
    if (event.subject_type === 'seminar') return 'triangle-seminar-bg';
    if (event.subject_type === 'lab') return 'triangle-lab-bg';
    return 'triangle-empty-bg';
  };

  // DIAGONAL SPLIT for ODD/EVEN - Use when any odd or even exists
  if (hasOdd || hasEven) {
    const oddEvent = oddWeekEvents[0];
    const evenEvent = evenWeekEvents[0];
    const oddBgClass = getTriangleBgClass(oddEvent);
    const evenBgClass = getTriangleBgClass(evenEvent);

    return (
      <td 
        className="schedule-cell border border-border p-0"
        style={{ height: `${height}px` }}
        rowSpan={rowSpan}
      >
        <div className="diagonal-wrapper">
          {/* TOP-LEFT TRIANGLE - ODD WEEK */}
          <div className={cn("triangle-clip triangle-odd", oddBgClass)}>
            {hasOdd ? (
              <div className="triangle-content triangle-content-odd">
                <EventBlock 
                  event={oddEvent} 
                  isCompact
                  onClick={() => onEventClick(oddEvent)} 
                />
              </div>
            ) : (
              <div 
                className="triangle-empty-zone triangle-empty-odd"
                onClick={onCellClick}
              >
                <Plus className="w-4 h-4 text-muted-foreground/30" />
              </div>
            )}
            <span className="glass-label glass-label-odd">Неч.</span>
          </div>
          
          {/* BOTTOM-RIGHT TRIANGLE - EVEN WEEK */}
          <div className={cn("triangle-clip triangle-even", evenBgClass)}>
            {hasEven ? (
              <div className="triangle-content triangle-content-even">
                <EventBlock 
                  event={evenEvent} 
                  isCompact
                  onClick={() => onEventClick(evenEvent)} 
                />
              </div>
            ) : (
              <div 
                className="triangle-empty-zone triangle-empty-even"
                onClick={onCellClick}
              >
                <Plus className="w-4 h-4 text-muted-foreground/30" />
              </div>
            )}
            <span className="glass-label glass-label-even">Чет.</span>
          </div>
        </div>
      </td>
    );
  }

  // FULL CELL for every-week events (1-2 events)
  if (everyWeekEvents.length > 0) {
    return (
      <td 
        className="schedule-cell border border-border p-0"
        style={{ height: `${height}px` }}
        rowSpan={rowSpan}
      >
        <div className="h-full w-full">
          {everyWeekEvents.length === 1 ? (
            <EventBlock 
              event={everyWeekEvents[0]} 
              onClick={() => onEventClick(everyWeekEvents[0])} 
            />
          ) : (
            <div className="flex gap-0.5 h-full p-1">
              {everyWeekEvents.slice(0, 2).map((event) => (
                <div key={event.id} className="flex-1 min-w-0">
                  <EventBlock 
                    event={event} 
                    isCompact
                    onClick={() => onEventClick(event)} 
                  />
                </div>
              ))}
            </div>
          )}
        </div>
      </td>
    );
  }

  // Fallback: render all events in a list
  return (
    <td 
      className="schedule-cell border border-border p-1"
      style={{ height: `${height}px` }}
      rowSpan={rowSpan}
    >
      <div className="h-full flex flex-col gap-1 overflow-hidden">
        {events.map((event) => (
          <EventBlock 
            key={event.id} 
            event={event} 
            isCompact
            onClick={() => onEventClick(event)} 
          />
        ))}
      </div>
    </td>
  );
}
