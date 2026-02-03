"use client"

import { useState, useEffect } from "react"
import { Calendar, Plus, BookOpen, Clock, MapPin, User } from "lucide-react"
import { Button } from "@/components/ui/button"
import { Card, CardContent, CardHeader, CardTitle } from "@/components/ui/card"
import { Badge } from "@/components/ui/badge"
import {
  Dialog,
  DialogContent,
  DialogHeader,
  DialogTitle,
  DialogTrigger,
} from "@/components/ui/dialog"
import { Input } from "@/components/ui/input"
import { Label } from "@/components/ui/label"
import {
  Select,
  SelectContent,
  SelectItem,
  SelectTrigger,
  SelectValue,
} from "@/components/ui/select"

interface ScheduleEvent {
  id: string
  title: string
  professor: string
  room: string
  day: string
  startTime: string
  endTime: string
  type: "lecture" | "seminar" | "lab"
  color: string
}

const DAYS = ["Понеделник", "Вторник", "Сряда", "Четвъртък", "Петък"]
const TIME_SLOTS = ["08:00", "09:00", "10:00", "11:00", "12:00", "13:00", "14:00", "15:00", "16:00", "17:00", "18:00"]

const TYPE_COLORS = {
  lecture: "bg-blue-100 border-blue-400 text-blue-800",
  seminar: "bg-green-100 border-green-400 text-green-800",
  lab: "bg-amber-100 border-amber-400 text-amber-800",
}

const TYPE_LABELS = {
  lecture: "Лекция",
  seminar: "Семинар",
  lab: "Лаборатория",
}

const initialEvents: ScheduleEvent[] = [
  {
    id: "1",
    title: "Математика 1",
    professor: "проф. Иванов",
    room: "2301",
    day: "Понеделник",
    startTime: "08:00",
    endTime: "10:00",
    type: "lecture",
    color: "blue",
  },
  {
    id: "2",
    title: "Програмиране",
    professor: "доц. Петров",
    room: "2205",
    day: "Понеделник",
    startTime: "10:00",
    endTime: "12:00",
    type: "lab",
    color: "amber",
  },
  {
    id: "3",
    title: "Физика",
    professor: "проф. Георгиев",
    room: "1101",
    day: "Вторник",
    startTime: "09:00",
    endTime: "11:00",
    type: "lecture",
    color: "blue",
  },
  {
    id: "4",
    title: "Английски език",
    professor: "ас. Стоянова",
    room: "3102",
    day: "Сряда",
    startTime: "13:00",
    endTime: "15:00",
    type: "seminar",
    color: "green",
  },
  {
    id: "5",
    title: "Електротехника",
    professor: "доц. Димитров",
    room: "2401",
    day: "Четвъртък",
    startTime: "08:00",
    endTime: "10:00",
    type: "lecture",
    color: "blue",
  },
  {
    id: "6",
    title: "CAD системи",
    professor: "гл.ас. Николов",
    room: "КК-203",
    day: "Петък",
    startTime: "14:00",
    endTime: "17:00",
    type: "lab",
    color: "amber",
  },
]

export default function SchedulePage() {
  const [events, setEvents] = useState<ScheduleEvent[]>(initialEvents)
  const [isModalOpen, setIsModalOpen] = useState(false)
  const [editingEvent, setEditingEvent] = useState<ScheduleEvent | null>(null)
  const [mounted, setMounted] = useState(false)

  const [formData, setFormData] = useState({
    title: "",
    professor: "",
    room: "",
    day: "Понеделник",
    startTime: "08:00",
    endTime: "10:00",
    type: "lecture" as "lecture" | "seminar" | "lab",
  })

  useEffect(() => {
    setMounted(true)
    const saved = localStorage.getItem("schedule-events")
    if (saved) {
      setEvents(JSON.parse(saved))
    }
  }, [])

  useEffect(() => {
    if (mounted) {
      localStorage.setItem("schedule-events", JSON.stringify(events))
    }
  }, [events, mounted])

  const getEventsForCell = (day: string, time: string) => {
    return events.filter((event) => {
      const eventStart = TIME_SLOTS.indexOf(event.startTime)
      const eventEnd = TIME_SLOTS.indexOf(event.endTime)
      const currentTime = TIME_SLOTS.indexOf(time)
      return event.day === day && currentTime >= eventStart && currentTime < eventEnd
    })
  }

  const isEventStart = (event: ScheduleEvent, time: string) => {
    return event.startTime === time
  }

  const getEventDuration = (event: ScheduleEvent) => {
    const startIndex = TIME_SLOTS.indexOf(event.startTime)
    const endIndex = TIME_SLOTS.indexOf(event.endTime)
    return endIndex - startIndex
  }

  const handleAddEvent = () => {
    setEditingEvent(null)
    setFormData({
      title: "",
      professor: "",
      room: "",
      day: "Понеделник",
      startTime: "08:00",
      endTime: "10:00",
      type: "lecture",
    })
    setIsModalOpen(true)
  }

  const handleEditEvent = (event: ScheduleEvent) => {
    setEditingEvent(event)
    setFormData({
      title: event.title,
      professor: event.professor,
      room: event.room,
      day: event.day,
      startTime: event.startTime,
      endTime: event.endTime,
      type: event.type,
    })
    setIsModalOpen(true)
  }

  const handleSaveEvent = () => {
    if (!formData.title) return

    if (editingEvent) {
      setEvents(events.map((e) => (e.id === editingEvent.id ? { ...e, ...formData } : e)))
    } else {
      const newEvent: ScheduleEvent = {
        id: Date.now().toString(),
        ...formData,
        color: formData.type === "lecture" ? "blue" : formData.type === "seminar" ? "green" : "amber",
      }
      setEvents([...events, newEvent])
    }
    setIsModalOpen(false)
  }

  const handleDeleteEvent = () => {
    if (editingEvent) {
      setEvents(events.filter((e) => e.id !== editingEvent.id))
      setIsModalOpen(false)
    }
  }

  if (!mounted) {
    return (
      <div className="flex items-center justify-center min-h-screen bg-slate-50">
        <div className="animate-pulse text-slate-500">Зареждане...</div>
      </div>
    )
  }

  return (
    <div className="min-h-screen bg-gradient-to-br from-slate-50 to-slate-100">
      <header className="bg-white border-b border-slate-200 sticky top-0 z-10">
        <div className="max-w-7xl mx-auto px-4 py-4 flex items-center justify-between">
          <div className="flex items-center gap-3">
            <div className="p-2 bg-blue-600 rounded-lg">
              <Calendar className="h-6 w-6 text-white" />
            </div>
            <div>
              <h1 className="text-xl font-bold text-slate-900">Учебен График</h1>
              <p className="text-sm text-slate-500">ТУ - София</p>
            </div>
          </div>
          <Button onClick={handleAddEvent} className="gap-2">
            <Plus className="h-4 w-4" />
            Добави занятие
          </Button>
        </div>
      </header>

      <main className="max-w-7xl mx-auto px-4 py-6">
        <Card className="overflow-hidden shadow-lg">
          <CardContent className="p-0">
            <div className="overflow-x-auto">
              <table className="w-full border-collapse min-w-[900px]">
                <thead>
                  <tr className="bg-slate-50">
                    <th className="w-20 p-3 text-left text-xs font-semibold text-slate-500 uppercase tracking-wider border-b border-r border-slate-200">
                      Час
                    </th>
                    {DAYS.map((day) => (
                      <th
                        key={day}
                        className="p-3 text-left text-xs font-semibold text-slate-500 uppercase tracking-wider border-b border-r last:border-r-0 border-slate-200"
                      >
                        {day}
                      </th>
                    ))}
                  </tr>
                </thead>
                <tbody>
                  {TIME_SLOTS.slice(0, -1).map((time, timeIndex) => (
                    <tr key={time} className="border-b border-slate-100 last:border-b-0">
                      <td className="p-2 text-sm font-medium text-slate-500 border-r border-slate-200 bg-slate-50/50 text-center">
                        {time}
                      </td>
                      {DAYS.map((day) => {
                        const cellEvents = getEventsForCell(day, time)
                        const startingEvents = cellEvents.filter((e) => isEventStart(e, time))

                        if (cellEvents.length > 0 && startingEvents.length === 0) {
                          return null
                        }

                        return (
                          <td
                            key={`${day}-${time}`}
                            className="p-1 border-r last:border-r-0 border-slate-200 align-top h-16 relative"
                            rowSpan={startingEvents.length > 0 ? getEventDuration(startingEvents[0]) : 1}
                          >
                            {startingEvents.map((event) => (
                              <button
                                key={event.id}
                                onClick={() => handleEditEvent(event)}
                                className={`w-full h-full p-2 rounded-lg border-l-4 text-left transition-all hover:shadow-md ${TYPE_COLORS[event.type]}`}
                              >
                                <div className="font-semibold text-sm truncate">{event.title}</div>
                                <div className="flex items-center gap-1 text-xs mt-1 opacity-80">
                                  <User className="h-3 w-3" />
                                  <span className="truncate">{event.professor}</span>
                                </div>
                                <div className="flex items-center gap-1 text-xs mt-0.5 opacity-80">
                                  <MapPin className="h-3 w-3" />
                                  <span>{event.room}</span>
                                </div>
                                <Badge variant="secondary" className="mt-1 text-[10px] px-1.5 py-0">
                                  {TYPE_LABELS[event.type]}
                                </Badge>
                              </button>
                            ))}
                          </td>
                        )
                      })}
                    </tr>
                  ))}
                </tbody>
              </table>
            </div>
          </CardContent>
        </Card>

        <div className="mt-6 flex gap-4 justify-center">
          {Object.entries(TYPE_LABELS).map(([type, label]) => (
            <div key={type} className="flex items-center gap-2">
              <div className={`w-4 h-4 rounded border-l-4 ${TYPE_COLORS[type as keyof typeof TYPE_COLORS]}`} />
              <span className="text-sm text-slate-600">{label}</span>
            </div>
          ))}
        </div>
      </main>

      <Dialog open={isModalOpen} onOpenChange={setIsModalOpen}>
        <DialogContent className="sm:max-w-md">
          <DialogHeader>
            <DialogTitle>{editingEvent ? "Редактиране на занятие" : "Ново занятие"}</DialogTitle>
          </DialogHeader>
          <div className="space-y-4 py-4">
            <div className="space-y-2">
              <Label htmlFor="title">Предмет</Label>
              <Input
                id="title"
                value={formData.title}
                onChange={(e) => setFormData({ ...formData, title: e.target.value })}
                placeholder="Име на предмета"
              />
            </div>
            <div className="space-y-2">
              <Label htmlFor="professor">Преподавател</Label>
              <Input
                id="professor"
                value={formData.professor}
                onChange={(e) => setFormData({ ...formData, professor: e.target.value })}
                placeholder="Име на преподавателя"
              />
            </div>
            <div className="space-y-2">
              <Label htmlFor="room">Зала</Label>
              <Input
                id="room"
                value={formData.room}
                onChange={(e) => setFormData({ ...formData, room: e.target.value })}
                placeholder="Номер на зала"
              />
            </div>
            <div className="grid grid-cols-2 gap-4">
              <div className="space-y-2">
                <Label>Ден</Label>
                <Select value={formData.day} onValueChange={(value) => setFormData({ ...formData, day: value })}>
                  <SelectTrigger>
                    <SelectValue />
                  </SelectTrigger>
                  <SelectContent>
                    {DAYS.map((day) => (
                      <SelectItem key={day} value={day}>
                        {day}
                      </SelectItem>
                    ))}
                  </SelectContent>
                </Select>
              </div>
              <div className="space-y-2">
                <Label>Тип</Label>
                <Select
                  value={formData.type}
                  onValueChange={(value: "lecture" | "seminar" | "lab") => setFormData({ ...formData, type: value })}
                >
                  <SelectTrigger>
                    <SelectValue />
                  </SelectTrigger>
                  <SelectContent>
                    <SelectItem value="lecture">Лекция</SelectItem>
                    <SelectItem value="seminar">Семинар</SelectItem>
                    <SelectItem value="lab">Лаборатория</SelectItem>
                  </SelectContent>
                </Select>
              </div>
            </div>
            <div className="grid grid-cols-2 gap-4">
              <div className="space-y-2">
                <Label>Начало</Label>
                <Select
                  value={formData.startTime}
                  onValueChange={(value) => setFormData({ ...formData, startTime: value })}
                >
                  <SelectTrigger>
                    <SelectValue />
                  </SelectTrigger>
                  <SelectContent>
                    {TIME_SLOTS.slice(0, -1).map((time) => (
                      <SelectItem key={time} value={time}>
                        {time}
                      </SelectItem>
                    ))}
                  </SelectContent>
                </Select>
              </div>
              <div className="space-y-2">
                <Label>Край</Label>
                <Select value={formData.endTime} onValueChange={(value) => setFormData({ ...formData, endTime: value })}>
                  <SelectTrigger>
                    <SelectValue />
                  </SelectTrigger>
                  <SelectContent>
                    {TIME_SLOTS.slice(1).map((time) => (
                      <SelectItem key={time} value={time}>
                        {time}
                      </SelectItem>
                    ))}
                  </SelectContent>
                </Select>
              </div>
            </div>
          </div>
          <div className="flex justify-between">
            {editingEvent && (
              <Button variant="destructive" onClick={handleDeleteEvent}>
                Изтрий
              </Button>
            )}
            <div className="flex gap-2 ml-auto">
              <Button variant="outline" onClick={() => setIsModalOpen(false)}>
                Отказ
              </Button>
              <Button onClick={handleSaveEvent}>Запази</Button>
            </div>
          </div>
        </DialogContent>
      </Dialog>
    </div>
  )
}
