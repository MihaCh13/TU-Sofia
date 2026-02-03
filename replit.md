# University Schedule Manager

## Overview
A Next.js 16 web application for managing university class schedules. The UI is in Bulgarian and allows users to:
- View weekly class schedules in a calendar grid format
- Add calendars and events
- Categorize events by type (lecture, seminar, lab, etc.)
- View different weeks (odd/even)

## Tech Stack
- **Framework**: Next.js 16 with TypeScript
- **React**: 19.2
- **Styling**: Tailwind CSS 4
- **UI Components**: Radix UI, shadcn/ui components
- **State Management**: Zustand
- **Forms**: React Hook Form with Zod validation
- **Charts**: Recharts

## Project Structure
```
weekly schedule/           # Main Next.js application
├── app/                   # App router pages
│   ├── globals.css        # Global styles
│   ├── layout.tsx         # Root layout
│   └── page.tsx           # Home page
├── components/            # React components
├── hooks/                 # Custom React hooks
├── lib/                   # Utility functions
├── public/                # Static assets
├── styles/                # Additional styles
├── next.config.mjs        # Next.js configuration
├── tsconfig.json          # TypeScript config
└── package.json           # Dependencies

C-codes/                   # C programming examples (not part of web app)
Python/                    # Python examples (not part of web app)
```

## Development
The dev server runs on port 5000:
```bash
cd "weekly schedule" && npm run dev -- -p 5000 -H 0.0.0.0
```

## Deployment
Configured for autoscale deployment with:
- Build: `npm run build`
- Start: `npm run start -- -p 5000 -H 0.0.0.0`

## Recent Changes
- Feb 3, 2026: Initial import and Replit environment setup
- Configured Next.js to allow all dev origins for Replit proxy
- Set up workflow for development server
