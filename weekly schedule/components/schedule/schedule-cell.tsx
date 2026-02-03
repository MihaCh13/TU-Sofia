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
  const regularEvents = events.filter(e => e.event_type !== 'makeup');
  const oddWeekEvents = regularEvents.filter(e => e.week_cycle === 'odd');
  const evenWeekEvents = regularEvents.filter(e => e.week_cycle === 'even');
  const everyWeekEvents = regularEvents.filter(e => e.week_cycle === 'every');

  const isEmpty = events.length === 0;

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

  // Single event for every week - FULL CELL
  if (everyWeekEvents.length > 0 && oddWeekEvents.length === 0 && evenWeekEvents.length === 0) {
    return (
      <td 
        className="schedule-cell border border-border p-0"
        style={{ height: `${height}px` }}
        rowSpan={rowSpan}
      >
        <div className="h-full w-full">
          {everyWeekEvents.map((event) => (
            <EventBlock 
              key={event.id} 
              event={event} 
              onClick={() => onEventClick(event)} 
            />
          ))}
        </div>
      </td>
    );
  }

  // Check for odd/even alternation
  const hasOdd = oddWeekEvents.length > 0;
  const hasEven = evenWeekEvents.length > 0;

  // Check total events for collision fallback (3+ events = stacked list)
  const totalOddEvenEvents = oddWeekEvents.length + evenWeekEvents.length;

  // DIAGONAL SPLIT for ODD/EVEN - Use diagonal layout when any odd or even exists and <= 2 total events
  if ((hasOdd || hasEven) && totalOddEvenEvents <= 2) {
    return (
      <td 
        className="schedule-cell border border-border p-0"
        style={{ height: `${height}px` }}
        rowSpan={rowSpan}
      >
        <div className="diagonal-container">
          {/* DIAGONAL LINE */}
          <div className="diagonal-line" />
          
          {/* TOP-LEFT TRIANGLE - ODD WEEK */}
          <div className="diagonal-odd">
            <div className="diagonal-label odd-label">Неч.</div>
            {hasOdd ? (
              <div className="diagonal-content odd-content">
                <EventBlock 
                  event={oddWeekEvents[0]} 
                  isCompact
                  onClick={() => onEventClick(oddWeekEvents[0])} 
                />
              </div>
            ) : (
              <div 
                className="diagonal-empty odd-empty"
                onClick={onCellClick}
              >
                <Plus className="w-4 h-4 text-muted-foreground/40" />
              </div>
            )}
          </div>
          
          {/* BOTTOM-RIGHT TRIANGLE - EVEN WEEK */}
          <div className="diagonal-even">
            <div className="diagonal-label even-label">Чет.</div>
            {hasEven ? (
              <div className="diagonal-content even-content">
                <EventBlock 
                  event={evenWeekEvents[0]} 
                  isCompact
                  onClick={() => onEventClick(evenWeekEvents[0])} 
                />
              </div>
            ) : (
              <div 
                className="diagonal-empty even-empty"
                onClick={onCellClick}
              >
                <Plus className="w-4 h-4 text-muted-foreground/40" />
              </div>
            )}
          </div>
        </div>
      </td>
    );
  }

  // COLLISION FALLBACK: 3+ odd/even events - stacked list view
  if ((hasOdd || hasEven) && totalOddEvenEvents > 2) {
    const allOddEvenEvents = [...oddWeekEvents, ...evenWeekEvents];
    return (
      <td 
        className="schedule-cell border border-border p-1"
        style={{ height: `${height}px` }}
        rowSpan={rowSpan}
      >
        <div className="h-full flex flex-col gap-1 overflow-hidden">
          {allOddEvenEvents.map((event) => (
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

  // Fallback: render all events
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
