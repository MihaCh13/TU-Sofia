'use client';

import { useState, useEffect } from 'react';
import { Button } from '@/components/ui/button';
import {
  Dialog,
  DialogContent,
  DialogHeader,
  DialogTitle,
  DialogFooter,
} from '@/components/ui/dialog';
import { Input } from '@/components/ui/input';
import { Label } from '@/components/ui/label';
import type { CalendarConfig } from '@/lib/schedule-types';
import { useScheduleStore } from '@/lib/schedule-store';

interface CalendarConfigModalProps {
  isOpen: boolean;
  onClose: () => void;
}

export function CalendarConfigModal({ isOpen, onClose }: CalendarConfigModalProps) {
  const [config, setConfig] = useState<CalendarConfig>({
    winterSemester: { start: '', end: '' },
    summerSemester: { start: '', end: '' },
    winterRegularSession: { start: '', end: '' },
    winterRetakeSession: { start: '', end: '' },
    summerRegularSession: { start: '', end: '' },
    annualRetakeSession: { start: '', end: '' },
    liquidationSession: { start: '', end: '' },
  });

  const { calendarConfig, setCalendarConfig } = useScheduleStore();

  useEffect(() => {
    if (calendarConfig) {
      setConfig(calendarConfig);
    }
  }, [isOpen, calendarConfig]);

  const handleInputChange = (
    section: keyof CalendarConfig,
    field: 'start' | 'end',
    value: string
  ) => {
    setConfig((prev) => ({
      ...prev,
      [section]: {
        ...prev[section],
        [field]: value,
      },
    }));
  };

  const handleSave = () => {
    setCalendarConfig(config);
    onClose();
  };

  const DateInput = ({
    label,
    section,
    field,
  }: {
    label: string;
    section: keyof CalendarConfig;
    field: 'start' | 'end';
  }) => (
    <div className="space-y-2">
      <Label htmlFor={`${section}-${field}`}>{label}</Label>
      <Input
        id={`${section}-${field}`}
        type="date"
        value={config[section][field]}
        onChange={(e) =>
          handleInputChange(section, field, e.target.value)
        }
      />
    </div>
  );

  return (
    <Dialog open={isOpen} onOpenChange={onClose}>
      <DialogContent className="sm:max-w-[600px] max-h-[90vh] overflow-y-auto">
        <DialogHeader>
          <DialogTitle>Calendar Configuration</DialogTitle>
        </DialogHeader>

        <div className="space-y-6">
          <div className="space-y-3">
            <h3 className="font-semibold text-sm">Semesters</h3>
            <div className="grid grid-cols-2 gap-3">
              <DateInput label="Winter Semester Start" section="winterSemester" field="start" />
              <DateInput label="Winter Semester End" section="winterSemester" field="end" />
              <DateInput label="Summer Semester Start" section="summerSemester" field="start" />
              <DateInput label="Summer Semester End" section="summerSemester" field="end" />
            </div>
          </div>

          <div className="space-y-3">
            <h3 className="font-semibold text-sm">Exam Sessions</h3>
            <div className="grid grid-cols-2 gap-3">
              <DateInput label="Winter Regular Session Start" section="winterRegularSession" field="start" />
              <DateInput label="Winter Regular Session End" section="winterRegularSession" field="end" />
              <DateInput label="Winter Retake Session Start" section="winterRetakeSession" field="start" />
              <DateInput label="Winter Retake Session End" section="winterRetakeSession" field="end" />
              <DateInput label="Summer Regular Session Start" section="summerRegularSession" field="start" />
              <DateInput label="Summer Regular Session End" section="summerRegularSession" field="end" />
              <DateInput label="Annual Retake Session Start" section="annualRetakeSession" field="start" />
              <DateInput label="Annual Retake Session End" section="annualRetakeSession" field="end" />
              <DateInput label="Liquidation Session Start" section="liquidationSession" field="start" />
              <DateInput label="Liquidation Session End" section="liquidationSession" field="end" />
            </div>
          </div>
        </div>

        <DialogFooter>
          <Button variant="outline" onClick={onClose}>
            Cancel
          </Button>
          <Button onClick={handleSave}>
            Save Configuration
          </Button>
        </DialogFooter>
      </DialogContent>
    </Dialog>
  );
}
