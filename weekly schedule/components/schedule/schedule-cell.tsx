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

  // HORIZONTAL SPLIT for ODD/EVEN - Always use split layout when any odd or even exists
  if (hasOdd || hasEven) {
    return (
      <td 
        className="schedule-cell border border-border p-0"
        style={{ height: `${height}px` }}
        rowSpan={rowSpan}
      >
        <div className="split-container">
          {/* TOP HALF - ODD WEEK */}
          <div className="split-top">
            <div className="split-label odd-label">Нечетна</div>
            <div className="split-content">
              {hasOdd ? (
                oddWeekEvents.length === 1 ? (
                  <EventBlock 
                    event={oddWeekEvents[0]} 
                    isCompact
                    onClick={() => onEventClick(oddWeekEvents[0])} 
                  />
                ) : (
                  <div className="flex gap-0.5 w-full h-full">
                    {oddWeekEvents.slice(0, 2).map((event) => (
                      <div key={event.id} className="flex-1 min-w-0">
                        <EventBlock 
                          event={event} 
                          isCompact
                          onClick={() => onEventClick(event)} 
                        />
                      </div>
                    ))}
                  </div>
                )
              ) : (
                <div 
                  className="h-full w-full flex items-center justify-center bg-muted/30 rounded cursor-pointer hover:bg-muted/50 transition-colors"
                  onClick={onCellClick}
                >
                  <Plus className="w-4 h-4 text-muted-foreground/40" />
                </div>
              )}
            </div>
          </div>
          
          {/* DIVIDER LINE */}
          <div className="split-divider" />
          
          {/* BOTTOM HALF - EVEN WEEK */}
          <div className="split-bottom">
            <div className="split-label even-label">Четна</div>
            <div className="split-content">
              {hasEven ? (
                evenWeekEvents.length === 1 ? (
                  <EventBlock 
                    event={evenWeekEvents[0]} 
                    isCompact
                    onClick={() => onEventClick(evenWeekEvents[0])} 
                  />
                ) : (
                  <div className="flex gap-0.5 w-full h-full">
                    {evenWeekEvents.slice(0, 2).map((event) => (
                      <div key={event.id} className="flex-1 min-w-0">
                        <EventBlock 
                          event={event} 
                          isCompact
                          onClick={() => onEventClick(event)} 
                        />
                      </div>
                    ))}
                  </div>
                )
              ) : (
                <div 
                  className="h-full w-full flex items-center justify-center bg-muted/30 rounded cursor-pointer hover:bg-muted/50 transition-colors"
                  onClick={onCellClick}
                >
                  <Plus className="w-4 h-4 text-muted-foreground/40" />
                </div>
              )}
            </div>
          </div>
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
