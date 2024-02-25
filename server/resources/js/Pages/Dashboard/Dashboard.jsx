import AuthenticatedLayout from '@/Layouts/AuthenticatedLayout';
import { Head } from '@inertiajs/react';
import SensorChart from './Partials/SensorChart';

export default function Dashboard({ auth }) {
    return (
        <AuthenticatedLayout
            user={auth.user}
            header={<h2 className="font-semibold text-xl text-gray-800 leading-tight">Dashboard</h2>}
        >
            <Head title="Dashboard" />

            <div className="grid py-12 grid-cols-2 place-items-center">
                <SensorChart></SensorChart>
                <SensorChart></SensorChart>
            </div>
        </AuthenticatedLayout>
    );
}