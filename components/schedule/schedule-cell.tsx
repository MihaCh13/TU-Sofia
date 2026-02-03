'use client';

import type { ScheduleEvent } from '@/lib/schedule-types';
import { cn } from '@/lib/utils';

interface ScheduleCellProps {
  events: ScheduleEvent[];
  rowSpan: number;
  height: number;
  onCellClick: () => void;
  onEventClick: (event: ScheduleEvent) => void;
}

export function ScheduleCell({
  events,
  rowSpan,
  height,
  onCellClick,
  onEventClick,
}: ScheduleCellProps) {
  return (
    <td
      rowSpan={rowSpan}
      style={{ height: `${height}px` }}
      className="px-2 py-2 border-r border-border last:border-r-0 cursor-pointer hover:bg-accent/50 transition-colors"
      onClick={onCellClick}
    >
      {events.length === 0 ? (
        <div className="h-full" />
      ) : (
        <div className="space-y-1 h-full">
          {events.map((event) => (
            <div
              key={event.id}
              className={cn(
                "p-2 rounded-md text-xs font-medium text-white cursor-pointer hover:shadow-md transition-shadow",
                "overflow-hidden text-ellipsis"
              )}
              style={{ 
                backgroundColor: event.color || '#3b82f6',
              }}
              onClick={(e) => {
                e.stopPropagation();
                onEventClick(event);
              }}
              title={`${event.title} - ${event.professor}`}
            >
              <div className="font-semibold truncate">{event.title}</div>
              <div className="text-xs opacity-90 truncate">{event.professor}</div>
              {event.room && <div className="text-xs opacity-75">{event.room}</div>}
            </div>
          ))}
        </div>
      )}
    </td>
  );
}
