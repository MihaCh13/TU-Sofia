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

  // FIX #2: DIAGONAL SPLIT for ODD/EVEN - Use when any odd or even exists
  if (hasOdd || hasEven) {
    return (
      <td 
        className="schedule-cell border border-border p-0"
        style={{ height: `${height}px` }}
        rowSpan={rowSpan}
      >
        <div className="diagonal-wrapper">
          {/* TOP-LEFT TRIANGLE - ODD WEEK */}
          <div className="triangle-clip triangle-odd">
            {hasOdd ? (
              <div className="triangle-content">
                <EventBlock 
                  event={oddWeekEvents[0]} 
                  isCompact
                  onClick={() => onEventClick(oddWeekEvents[0])} 
                />
              </div>
            ) : (
              <div 
                className="triangle-empty"
                onClick={onCellClick}
              >
                <Plus className="w-4 h-4 text-muted-foreground/30" />
              </div>
            )}
            <span className="glass-label glass-label-odd">Неч.</span>
          </div>
          
          {/* BOTTOM-RIGHT TRIANGLE - EVEN WEEK */}
          <div className="triangle-clip triangle-even">
            {hasEven ? (
              <div className="triangle-content">
                <EventBlock 
                  event={evenWeekEvents[0]} 
                  isCompact
                  onClick={() => onEventClick(evenWeekEvents[0])} 
                />
              </div>
            ) : (
              <div 
                className="triangle-empty"
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
