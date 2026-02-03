'use client';

import { useState, useEffect } from 'react';
import { Button } from '@/components/ui/button';
import { Plus, GraduationCap, CalendarPlus } from 'lucide-react';
import { useScheduleStore } from '@/lib/schedule-store';
import { CalendarConfigModal } from './calendar-config-modal';

interface HeaderProps {
  onAddEvent: () => void;
}

export function Header({ onAddEvent }: HeaderProps) {
  const [isCalendarModalOpen, setIsCalendarModalOpen] = useState(false);
  const [mounted, setMounted] = useState(false);
  const calendarConfig = useScheduleStore((state) => state.calendarConfig);
  const semester = useScheduleStore((state) => state.semester);

  useEffect(() => {
    setMounted(true);
  }, []);

  const semesterLabel = semester === 'winter' ? 'Winter Semester' : 'Summer Semester';

  return (
    <header className="bg-card/80 backdrop-blur-md shadow-sm border-b border-primary/10 px-6 py-5 flex-shrink-0">
      <div className="flex items-center justify-between">
        <div>
          <h1 className="text-2xl font-bold bg-gradient-to-r from-primary to-primary/70 bg-clip-text text-transparent flex items-center gap-3">
            <GraduationCap className="w-7 h-7 text-primary" />
            <span>Schedule</span>
          </h1>
          <p className="text-sm text-muted-foreground mt-1">
            {mounted && calendarConfig ? semesterLabel : 'Manage your class schedule'}
          </p>
        </div>
        <div className="flex items-center gap-3">
          <Button 
            variant="outline"
            onClick={() => setIsCalendarModalOpen(true)}
            className="border-primary/30 hover:border-primary hover:bg-primary/5 bg-transparent"
          >
            <CalendarPlus className="w-4 h-4 mr-2" />
            {mounted && calendarConfig ? 'Edit Calendar' : 'Setup Calendar'}
          </Button>
          <Button 
            onClick={onAddEvent}
            className="bg-gradient-to-r from-primary to-primary/80 hover:from-primary/90 hover:to-primary/70 shadow-lg"
          >
            <Plus className="w-4 h-4 mr-2" />
            Add Class
          </Button>
        </div>
      </div>
      
      <CalendarConfigModal 
        isOpen={isCalendarModalOpen} 
        onClose={() => setIsCalendarModalOpen(false)} 
      />
    </header>
  );
}
