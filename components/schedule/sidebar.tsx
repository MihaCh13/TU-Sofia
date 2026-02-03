'use client';

import { useEffect, useState } from 'react';
import { useScheduleStore } from '@/lib/schedule-store';
import { Card } from '@/components/ui/card';
import { Badge } from '@/components/ui/badge';
import { ScrollArea } from '@/components/ui/scroll-area';

export function Sidebar() {
  const [mounted, setMounted] = useState(false);
  const events = useScheduleStore((state) => state.events);

  useEffect(() => {
    useScheduleStore.persist.rehydrate();
    setMounted(true);
  }, []);

  if (!mounted) {
    return <div className="w-64 bg-card border-r border-border" />;
  }

  const totalCredits = events.reduce((sum, event) => sum + (event.credits || 0), 0);
  const uniqueProfessors = new Set(events.map((e) => e.professor).filter(Boolean)).size;

  return (
    <div className="w-64 bg-card border-r border-border flex flex-col flex-shrink-0">
      <div className="flex-1 overflow-hidden flex flex-col">
        {/* Stats */}
        <div className="p-4 space-y-3 border-b border-border">
          <div className="space-y-1">
            <p className="text-xs font-semibold text-muted-foreground uppercase">Total Classes</p>
            <p className="text-2xl font-bold">{events.length}</p>
          </div>
          {totalCredits > 0 && (
            <div className="space-y-1">
              <p className="text-xs font-semibold text-muted-foreground uppercase">Credits</p>
              <p className="text-2xl font-bold">{totalCredits}</p>
            </div>
          )}
          {uniqueProfessors > 0 && (
            <div className="space-y-1">
              <p className="text-xs font-semibold text-muted-foreground uppercase">Professors</p>
              <p className="text-2xl font-bold">{uniqueProfessors}</p>
            </div>
          )}
        </div>

        {/* Classes List */}
        {events.length > 0 ? (
          <ScrollArea className="flex-1">
            <div className="p-4 space-y-2">
              <p className="text-xs font-semibold text-muted-foreground uppercase mb-3">Classes</p>
              {events.map((event) => (
                <Card
                  key={event.id}
                  className="p-3 space-y-1 hover:bg-accent transition-colors cursor-pointer border"
                  style={{ borderLeftColor: event.color, borderLeftWidth: '4px' }}
                >
                  <div className="font-semibold text-sm line-clamp-2">{event.title}</div>
                  {event.professor && (
                    <div className="text-xs text-muted-foreground line-clamp-1">{event.professor}</div>
                  )}
                  <div className="flex gap-1 flex-wrap pt-1">
                    <Badge variant="outline" className="text-xs">
                      {event.day}
                    </Badge>
                    <Badge variant="secondary" className="text-xs">
                      {event.start_time}
                    </Badge>
                  </div>
                  {event.credits && (
                    <div className="text-xs text-muted-foreground pt-1">
                      {event.credits} credits
                    </div>
                  )}
                </Card>
              ))}
            </div>
          </ScrollArea>
        ) : (
          <div className="flex-1 flex items-center justify-center p-4">
            <div className="text-center space-y-2">
              <p className="text-sm text-muted-foreground">No classes yet</p>
              <p className="text-xs text-muted-foreground">Add a class to get started</p>
            </div>
          </div>
        )}
      </div>
    </div>
  );
}
