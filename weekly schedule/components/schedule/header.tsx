'use client';

import { Button } from '@/components/ui/button';
import { PlusCircle, Calendar, GraduationCap } from 'lucide-react';

interface HeaderProps {
  onAddEvent: () => void;
}

export function Header({ onAddEvent }: HeaderProps) {
  return (
    <header className="border-b bg-card px-6 py-4">
      <div className="flex items-center justify-between">
        <div className="flex items-center gap-3">
          <div className="flex items-center justify-center w-10 h-10 rounded-lg bg-primary/10">
            <GraduationCap className="w-6 h-6 text-primary" />
          </div>
          <div>
            <h1 className="text-xl font-bold text-foreground">Седмичен график</h1>
            <p className="text-sm text-muted-foreground">ТУ София - Зимен семестър 2024/2025</p>
          </div>
        </div>
        <div className="flex items-center gap-3">
          <Button variant="outline" size="sm" className="gap-2">
            <Calendar className="w-4 h-4" />
            Календар
          </Button>
          <Button onClick={onAddEvent} size="sm" className="gap-2">
            <PlusCircle className="w-4 h-4" />
            Добави занятие
          </Button>
        </div>
      </div>
    </header>
  );
}
